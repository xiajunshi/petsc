#ifndef included_ALE_Sifter_hh
#define included_ALE_Sifter_hh


#include <boost/multi_index_container.hpp>
#include <boost/multi_index/key_extractors.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/composite_key.hpp>

#include <iostream>


#ifndef  included_ALE_hh
#include <ALE.hh>
#endif


namespace ALE { 

  class XObject {
  protected:
    int      _debug;
  public:
    XObject(const int debug = 0)    : _debug(debug) {};
    XObject(const XObject& xobject) : _debug(xobject._debug) {};
    //
    int      debug(const int& debug = -1) {if(debug >= 0) {this->_debug = debug;} return this->_debug;};
  };// class XObject

  class XParallelObject : public XObject {
  protected:
    MPI_Comm _comm;
    int      _commRank, _commSize;
  protected:
    void __setupComm(const MPI_Comm& comm) {
      this->_comm = comm;
      PetscErrorCode ierr;
      ierr = MPI_Comm_size(this->_comm, &this->_commSize); CHKERROR(ierr, "Error in MPI_Comm_size");
      ierr = MPI_Comm_rank(this->_comm, &this->_commRank); CHKERROR(ierr, "Error in MPI_Comm_rank");
    }
  public:
    XParallelObject(const MPI_Comm& comm, const int debug)   : XObject(debug) {this->__setupComm(comm);};
    XParallelObject(const MPI_Comm& comm = PETSC_COMM_WORLD) : XObject()      {this->__setupComm(comm);};
    XParallelObject(const XParallelObject& xpobject)         : XObject(xpobject), _comm(xpobject._comm) {};
    //
    MPI_Comm comm()     {return this->_comm;};
    int      commSize() {return this->_commSize;};
    int      commRank() {return this->_commRank;};
  };// class XParallelObject
  
  namespace XSifterDef {
    // 
    // Arrow definition
    // 
    template<typename Source_, typename Target_, typename Color_>
    struct  Arrow { 
      typedef Arrow   arrow_type;
      typedef Source_ source_type;
      typedef Target_ target_type;
      typedef Color_  color_type;
      source_type _source;
      target_type _target;
      color_type  _color;
      //
      source_type source() const {return this->_source;};
      target_type target() const {return this->_target;};
      color_type  color()  const {return this->_color;};
      // Basic
      Arrow(const source_type& s, const target_type& t, const color_type& c) : _source(s), _target(t), _color(c) {};
      // Rebinding
      template <typename OtherSource_, typename OtherTarget_, typename OtherColor_>
      struct rebind {
        typedef Arrow<OtherSource_, OtherTarget_, OtherColor_> type;
      };
      // Flipping
      struct flip {
        typedef Arrow<target_type, source_type, color_type> type;
        type arrow(const arrow_type& a) { return type(a.target, a.source, a.color);};
      };
      // Printing
      friend std::ostream& operator<<(std::ostream& os, const Arrow& a) {
        os << a._source << " --(" << a._color << ")--> " << a._target;
        return os;
      }
      // Modifying
      struct sourceChanger {
        sourceChanger(const source_type& newSource) : _newSource(newSource) {};
        void operator()(arrow_type& a) {a._source = this->_newSource;}
      private:
        source_type _newSource;
      };
      //
      struct targetChanger {
        targetChanger(const target_type& newTarget) : _newTarget(newTarget) {};
        void operator()(arrow_type& a) { a._target = this->_newTarget;}
      private:
        const target_type _newTarget;
      };
      //
      struct colorChanger {
        colorChanger(const color_type& newColor) : _newColor(newColor) {};
        void operator()(arrow_type& a) { a._color = this->_newColor;}
      private:
        const color_type _newColor;
      };
    };// struct Arrow
    

    //
    // Rec orders
    //
    // RecKeyOrder compares records by comparing keys of type Key_ extracted from arrows using a KeyExtractor_.
    // In addition, a recordcan be compared to a single Key_ or another CompatibleKey_.
    template<typename Rec_, typename KeyExtractor_, typename KeyOrder_ = std::less<typename KeyExtractor_::result_type> >
    struct RecKeyOrder {
      typedef Rec_                                     rec_type;
      typedef KeyExtractor_                            key_extractor_type;
      typedef typename key_extractor_type::result_type key_type;
      typedef KeyOrder_                                key_order_type;
    protected:
      key_order_type     _key_order;
      key_extractor_type _kex;
    public:
      bool operator()(const rec_type& rec1, const rec_type& rec2) const {
        return this->_key_order(this->_kex(rec1), this->_kex(rec2));
      };
      template <typename CompatibleKey_>
      bool operator()(const rec_type& rec, const ALE::singleton<CompatibleKey_> keySingleton) const {
        // In order to disamiguate calls such as this from (rec&,rec&) calls, compatible keys are passed in wrapped as singletons, 
        // and must be unwrapped before the ordering operator is applied
        return this->_key_order(this->_kex(rec), keySingleton.first);
      };
      template <typename CompatibleKey_>
      bool operator()(const ALE::singleton<CompatibleKey_> keySingleton, const rec_type& rec) const {
        // In order to disamiguate calls such as this from (rec&,rec&) calls, compatible keys are passed in wrapped as singletons, 
        // and must be unwrapped before the ordering operator is applied
        return this->_key_order(keySingleton.first, this->_kex(rec));
      };
    };// RecKeyOrder

    //
    // Composite Rec ordering operators (e.g., used to generate cone and support indices for Arrows).
    // An RecKeyXXXOrder first orders on a single key using KeyOrder (e.g., Target or Source for cone and support respectively),
    // and then on the whole Rec, using an additional predicate XXXOrder.
    // These are then specialized (with Rec = Arrow) to SupportCompare & ConeCompare, using the order operators supplied by the user:
    // SupportOrder = (SourceOrder, SupportXXXOrder), 
    // ConeOrder    = (TargetOrder, ConeXXXOrder), etc
    template <typename Rec_, typename KeyExtractor_, typename KeyOrder_, typename XXXOrder_>
    struct RecKeyXXXOrder {
      typedef Rec_                                                             rec_type;
      typedef KeyExtractor_                                                    key_extractor_type;
      typedef KeyOrder_                                                        key_order_type;
      typedef typename key_extractor_type::result_type                         key_type;
      typedef XXXOrder_                                                        xxx_order_type;
      //
    private:
      key_order_type     _compare_keys;
      xxx_order_type     _compare_xxx;
      key_extractor_type _kex;
    public:
      bool operator()(const rec_type& rec1, const rec_type& rec2) const { 
        //
        return this->_compare_keys(_kex(rec1),_kex(rec2)) ||
          (!this->_compare_keys(_kex(rec2),_kex(rec1)) && this->_compare_xxx(rec1,rec2));
      };
      template <typename CompatibleKey_>
      bool operator()(const ALE::singleton<CompatibleKey_>& keySingleton, const rec_type& rec1) const {
        // In order to disamiguate calls such as this from (rec&,rec&) calls, compatible keys are passed in wrapped as singletons, 
        // and must be unwrapped before the ordering operator is applied
        //
        // We want key to be less than any (key, ...)
        return this->_compare_keys(keySingleton.first, this->_kex(rec1));
      };
      template <typename CompatibleKey_>
      bool operator()(const rec_type& rec1, const ALE::singleton<CompatibleKey_>& keySingleton) const {
        // In order to disamiguate calls such as this from (rec&,rec&) calls, compatible keys are passed in wrapped as singletons, 
        // and must be unwrapped before the ordering operator is applied
        //
        // We want key to be less than any (key, ...)
        return !this->_compare_keys(keySingleton.first, this->_kex(rec1));
      };
      template <typename CompatibleKey_, typename CompatibleXXXKey_>
      bool operator()(const ALE::pair<CompatibleKey_, CompatibleXXXKey_>& keyPair, const rec_type& rec) const {
        // In order to disamiguate calls such as this from (rec&,rec&) calls, compatible keys are passed in wrapped as singletons, 
        // and must be unwrapped before the ordering operator is applied
        //
        // We want (key,xxxkey) to be less than any (key, xxxkey, ...)
        return this->_compare_keys(keyPair.first, _kex(rec)) ||
          (!this->_compare_keys(_kex(rec), keyPair.first) && this->_compare_xxx(ALE::singleton<CompatibleXXXKey_>(keyPair.second),rec));
        // Note that CompatibleXXXKey_ -- the second key in the pair -- must be wrapped up as a singleton before being passed for comparison against rec
        // to compare_xxx.  This is necessary for compare_xxx to disamiguate comparison of recs to elements of differents types.  In particular, 
        // this is necessary if compare_xxx is of the RecKeyXXXOrder type. Specialization doesn't work, or I don't know how to make it work in this context.
      };
      template <typename CompatibleKey_, typename CompatibleXXXKey_>
      bool operator()(const rec_type& rec, const ALE::pair<CompatibleKey_, CompatibleXXXKey_>& keyPair) const {
        // We want (key,xxxkey) to be less than any (key, xxxkey, ...)
        return _compare_keys(_kex(rec), keyPair.first) ||
          (!this->_compare_keys(keyPair.first, _kex(rec)) && this->_compare_xxx(rec, ALE::singleton<CompatibleXXXKey_>(keyPair.second)));
        // Note that CompatibleXXXKey_ -- the second key in the pair -- must be wrapped up as a singleton before being passed for comparison against rec
        // to compare_xxx.  This is necessary for compare_xxx to disamiguate comparison of recs to elements of differents types.  In particular, 
        // this is necessary if compare_xxx is of the RecKeyXXXOrder type. Specialization doesn't work, or I don't know how to make it work in this context.
      };
    };// class RecKeyXXXOrder

    //
    // Default orders.
    //
    template<typename Arrow_, 
             typename SourceOrder_ = std::less<typename Arrow_::source_type>,
             typename ColorOrder_  = std::less<typename Arrow_::color_type> >
    struct SourceColorOrder : 
      public RecKeyXXXOrder<Arrow_, 
                            ::boost::multi_index::const_mem_fun<Arrow_,typename Arrow_::source_type, &Arrow_::source>, 
                            SourceOrder_, 
                            RecKeyOrder<Arrow_, 
                                        ::boost::multi_index::const_mem_fun<Arrow_, typename Arrow_::color_type, &Arrow_::color>, 
                                        ColorOrder_>
      >
    {};
    
    //
    template<typename Arrow_,
             typename ColorOrder_  = std::less<typename Arrow_::color_type>,
             typename SourceOrder_ = std::less<typename Arrow_::source_type>
    >
    struct ColorSourceOrder : 
      public RecKeyXXXOrder<Arrow_, 
                            ::boost::multi_index::const_mem_fun<Arrow_,typename Arrow_::color_type, &Arrow_::source>, 
                            ColorOrder_,
                            RecKeyOrder<Arrow_, 
                                        ::boost::multi_index::const_mem_fun<Arrow_, typename Arrow_::source_type, &Arrow_::source>, 
                                        SourceOrder_>
      >
    {};
    //
    template<typename Arrow_, 
             typename TargetOrder_ = std::less<typename Arrow_::source_type>,
             typename ColorOrder_  = std::less<typename Arrow_::color_type> >
    struct TargetColorOrder : 
      public RecKeyXXXOrder<Arrow_, 
                            ::boost::multi_index::const_mem_fun<Arrow_,typename Arrow_::source_type, &Arrow_::source>, 
                            TargetOrder_,
                            RecKeyOrder<Arrow_, 
                                        ::boost::multi_index::const_mem_fun<Arrow_, typename Arrow_::color_type, &Arrow_::color>, 
                                        ColorOrder_>
      >
    {};
    //
    template<typename Arrow_, 
             typename ColorOrder_  = std::less<typename Arrow_::color_type>,
             typename TargetOrder_ = std::less<typename Arrow_::source_type> >
    struct ColorTargetOrder : 
      public RecKeyXXXOrder<Arrow_, 
                            ::boost::multi_index::const_mem_fun<Arrow_,typename Arrow_::color_type, &Arrow_::source>, 
                            ColorOrder_,
                            RecKeyOrder<Arrow_, 
                                        ::boost::multi_index::const_mem_fun<Arrow_, typename Arrow_::source_type, &Arrow_::source>, 
                                        TargetOrder_>
      >
    {};
  
    
    //
    // PredicateTraits encapsulates Predicate types encoding object subsets with a given Predicate value or within a value range.
    template<typename Predicate_> 
    struct PredicateTraits {};
    // Traits of different predicate types are defined via specialization of PredicateTraits.
    // We require that the predicate type act like a signed int.
    template<>
    struct PredicateTraits<int> {
      typedef      int  predicate_type;
      typedef      int  printable_type;
      //
      static const predicate_type third;
      static const predicate_type max;
      static const predicate_type min;
    };
    const PredicateTraits<int>::predicate_type PredicateTraits<int>::max   = INT_MAX;
    const PredicateTraits<int>::predicate_type PredicateTraits<int>::min   = INT_MIN;
    const PredicateTraits<int>::predicate_type PredicateTraits<int>::third = (abs(INT_MIN)<abs(INT_MAX))?abs(INT_MIN)/3:abs(INT_MAX)/3;
    //
    template<>
    struct PredicateTraits<short> {
      typedef      short  predicate_type;
      typedef      short  printable_type;
      //
      static const predicate_type third;
      static const predicate_type max;
      static const predicate_type min;
    };
    const PredicateTraits<short>::predicate_type PredicateTraits<short>::max   = SHRT_MAX;
    const PredicateTraits<short>::predicate_type PredicateTraits<short>::min   = SHRT_MIN;
    const PredicateTraits<short>::predicate_type PredicateTraits<short>::third = (abs(SHRT_MIN)<abs(SHRT_MAX))?abs(SHRT_MIN)/3:abs(SHRT_MAX)/3;;
    //
    template<>
    struct PredicateTraits<char> {
      typedef char  predicate_type;
      typedef short printable_type;
      //
      static const predicate_type third;
      static const predicate_type max;
      static const predicate_type min;
    };
    const PredicateTraits<char>::predicate_type PredicateTraits<char>::max   = CHAR_MAX;
    const PredicateTraits<char>::predicate_type PredicateTraits<char>::min   = CHAR_MIN;
    const PredicateTraits<char>::predicate_type PredicateTraits<char>::third = (abs(CHAR_MIN)<abs(CHAR_MAX))?abs(CHAR_MIN)/3:abs(CHAR_MAX)/3;


    //
    // FilterManagers
    //
    template <typename Index_, typename FilterKeyExtractor_>
    class DummyFilterManager {
    public:
      typedef Index_                                   index_type;
      typedef FilterKeyExtractor_                      key_extractor_type;
      typedef typename key_extractor_type::result_type key_type;
    protected:
      index_type& _index;
    public:
      //
      DummyFilterManager(index_type& index)            : _index(index) {};
      DummyFilterManager(const DummyFilterManager& ff) : _index(ff._index) {};
      //
      index_type& index() {return this->_index;};
    };
    
    //
    // RangeFilter is a managed filter that defines a subset of index_type index based on 
    // the high and low value of key_type key.  
    // The types of the index and the key on which filtering is done are defined by the FilterManager.
    // 
    #undef  __CLASS__
    #define __CLASS__ "RangeFilter"
    template <typename FilterManager_>
    class RangeFilter : XObject {
    public:
      typedef FilterManager_                                   filter_manager_type;
      typedef typename filter_manager_type::index_type         index_type;
      typedef typename filter_manager_type::key_extractor_type key_extractor_type;
      typedef typename key_extractor_type::result_type         key_type;
      typedef PredicateTraits<key_type>                        key_traits;
      typedef typename index_type::iterator                    iterator;
    protected:
      filter_manager_type *_manager;
      bool                _have_low, _have_high;
      key_type            _low, _high;
      key_extractor_type  _kex;
    public:
      RangeFilter(filter_manager_type* manager) : 
        XObject(), _manager(manager), _have_low(false), _have_high(false) {};
      RangeFilter(filter_manager_type* manager, const key_type& low, const key_type& high) : 
        XObject(), _manager(manager), _have_low(true), _have_high(true), _low(low), _high(high)  {};
      RangeFilter(const RangeFilter& f) : 
        XObject(f), _manager(f._manager), _have_low(f._have_low), _have_high(f._have_high), _low(f._low), _high(f._high) {};
      ~RangeFilter(){};
      //
      void setLow(const key_type& low)   {this->_low  = low;  this->_have_low  = true;};
      void setHigh(const key_type& high) {this->_high = high; this->_have_high = true;};
      //
      key_type         low()       const {return this->_low;};
      key_type         high()      const {return this->_high;};
      bool             haveLow()   const {return this->_have_low;};
      bool             haveHigh()  const {return this->_have_high;};
      //
      key_type         key(const iterator& iter)  const { return this->_kex(*iter);};
      //
      // Returns the start of the allowed segment within the index.
      iterator begin() {         
        if(this->debug()) {
          std::cout << std::endl << __CLASS__ << "::" << __FUNCT__ << ": ";
          std::cout << "filter: " << *this << std::endl;
        }
        iterator iter;
        if(this->_have_low) {
          // ASSUMPTION: index ordering operator can compare against key_type singleton
          iter = this->_manager->index().lower_bound(ALE::singleton<key_type>(this->_low));
        }
        else {
          iter = this->_manager->index().begin();
        }
        if(this->debug()){
          //
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "*iter " << *iter; 
        }
        return iter;
      };
      // Returns the start of the allowed subsegment within a segment defined by fixing the outer key as in the current iterator,
      // while the filtering is done on the inner key.  The outer key is extracted using a OuterFilter, although only the
      // key extraction capabilities of OuterFilter are used.
      template<typename OuterFilter_>
      iterator begin(const iterator& outer_iter, const OuterFilter_& outer_filter) { 
        typedef typename OuterFilter_::key_type outer_key_type;
        iterator iter = outer_iter;
        if(this->debug()) {
          std::cout << std::endl << __CLASS__ << "::" << __FUNCT__ << ": ";
          std::cout << "filter: " << *this << ", outer filter: " << outer_filter  << ", *outer_iter: " << *outer_iter << std::endl;
        }
        if(this->_have_low) {
          // Find the lowest iterator in the range of the filter with the same outer_key
          // ASSUMPTION: index ordering operator can compare against (outer_key_type,key_type) pairs
          iter = this->_manager->index().lower_bound(ALE::pair<outer_key_type,key_type>(outer_filter.key(iter),this->_low));
        }
        else {
          // If the range is open from below (!have_low), we leave the iter alone
        }
        if(this->debug()){
          //
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "*iter " << *iter; 
        }
        return iter;
      };
      #undef  __FUNCT__
      #define __FUNCT__ "end"
      // Returns the start of the allowed segment within the index.
      iterator end() {
        if(this->debug()) {
          std::cout << std::endl << __CLASS__ << "::" << __FUNCT__ << ": ";
          std::cout << "filter: " << *this;
        }
        static iterator iter;
        // Determine the upper limit
        if(this->_have_high()) {
          // ASSUMPTION: index ordering operator can compare against (key_type) singletons
          iter = this->_manager->index().upper_bound(ALE::singleton<key_type>(this->high()));
        }
        else {
          iter = this->_manager->index().rbegin();
        }
        if(this->debug()){
          //
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "*iter " << *iter; 
        }
        return iter;
      };//end()

      #undef  __FUNCT__
      #define __FUNCT__ "end"
      // Returns the end of the allowed subsegment within a segment defined by fixing the outer key as in the current iterator,
      // while the filtering is done on the inner key.  The outer key is extracted using a OuterFilter, although only the
      // key extraction capabilities of OuterFilter are used.
      template <typename OuterFilter_>
      iterator end(const iterator& outer_iter, const OuterFilter_& outer_filter) {
        typedef typename OuterFilter_::key_type outer_key_type;
        iterator iter = outer_iter;
        if(this->debug()) {
          std::cout << std::endl << __CLASS__ << "::" << __FUNCT__ << ": ";
          std::cout << "filter: " << *this << ", outer filter: " << outer_filter << ", *outer_iter: " << *outer_iter << std::endl;
        }
        if(this->_have_high) {
          // Find the highest iterator in the range of the filter with the same outer_key
          // ASSUMPTION: index ordering operator can compare against (outer_key_type,key_type) pairs
          iter = this->_manager->index().upper_bound(ALE::pair<outer_key_type,key_type>(outer_filter.key(iter),this->_low));
        }
        else {
          // If the range is open from above (!have_high), we leave the iter alone
        }
        if(this->debug()){
          //
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "*iter " << *iter; 
        }
        return iter;
      };//end()
      //
      friend std::ostream& operator<<(std::ostream& os, const RangeFilter& f) {
        os << "[";
        if(f.haveLow()){
          os << ((typename key_traits::printable_type)(f.low())) << ",";
        }
        else {
          os << "none, ";
        }
        if(f.haveHigh()) {
          os << ((typename key_traits::printable_type)(f.high())); 
        }
        else {
          os << "none";
        }
        os << "]";
        return os;
      };
      friend std::ostream& operator<<(std::ostream& os, const Obj<RangeFilter>& f) {
        return (os << f.object());
      };
    };// RangeFilter

    //
    // FilteredIndexSequence definition
    // 
    //   Defines a sequence representing a subset of a multi_index container defined by its Index_ which is ordered lexicographically.
    // The ordering is controlled by a pair of filters (OuterFilter_ and InnerFilter_ types).
    // The elements of the sequence are a subset of an Index_ ordered lexicographically by (OuterKey_,InnerKey_) pairs and such that 
    // each key lies in the range of OuterFilter_/InnerFilter_ respectively.  
    // A sequence defines output iterators (input iterators in std terminology) for traversing a subset of an Index_ object.
    // Upon dereferencing values are extracted from each result record using a ValueExtractor_ object.
    //   More precisely, the index can be viewed as oredered by (OuterKey_,InnerKey_,RemainderKey_) triples, where the RemainderKey_
    // type is not explicitly known to FilteredIndexSequence.  The Filters only restrict the allowable values of the first two keys, 
    // while all RemainderKey_ values are allowed. By default a FilteredIndexSequence will traverse ALL entries with a given leading 
    // (OuterKey_,InnerKey_) pair.  However, setting the template parameter 'Strided = true' will cause only the first elements of 
    // each segment with the same (OuterKey_,InnerKey_) pair to be traversed.  In other words, each (OuterKey_,InnerKey_) pair will 
    // be seen once only.  
    //   Ideally, 'Strided' should parameterize different implementations, but right now there is an 'if' test. An opporunity for improvement.
    // 
    #undef  __CLASS__
    #define __CLASS__ "FilteredIndexSequence"
    template <typename Index_, typename OuterFilter_, typename InnerFilter_, 
              typename ValueExtractor_ = ::boost::multi_index::identity<typename Index_::value_type>, bool Strided = false >
    struct FilteredIndexSequence : XObject {
      typedef Index_                                           index_type;
      typedef InnerFilter_                                     inner_filter_type;
      typedef OuterFilter_                                     outer_filter_type;
      //
      typedef typename outer_filter_type::key_extractor_type   outer_key_extractor_type;
      typedef typename outer_key_extractor_type::result_type   outer_key_type;
      typedef typename inner_filter_type::key_extractor_type   inner_key_extractor_type;
      typedef typename inner_key_extractor_type::result_type   inner_key_type;
      //
      typedef ValueExtractor_                                  value_extractor_type;
      typedef typename value_extractor_type::result_type       value_type;
      typedef typename index_type::size_type                   size_type;
      //
      typedef typename index_type::iterator                    itor_type;
      typedef typename index_type::reverse_iterator            ritor_type;
      //
      class iterator {
      public:
        // Parent sequence type
        typedef FilteredIndexSequence                   sequence_type;
        // Standard iterator typedefs
        typedef std::input_iterator_tag                iterator_category;
        typedef int                                    difference_type;
        typedef value_type*                            pointer;
        typedef value_type&                            reference;
        /* value_type defined in the containing FilteredIndexSequence */
      protected:
        // Parent sequence
        sequence_type  *_sequence;
        // Underlying iterator & segment boundary
        itor_type       _itor;
        itor_type       _segBndry;
        //
        // Value extractor
        outer_key_extractor_type _okex;
        inner_key_extractor_type _ikex;
        value_extractor_type     _ex;
      public:
        iterator() : _sequence(NULL) {};
        iterator(sequence_type *sequence, const itor_type& itor, const itor_type& segBndry) : 
          _sequence(sequence), _itor(itor), _segBndry(segBndry) {};
        iterator(const iterator& iter):_sequence(iter._sequence), _itor(iter._itor),_segBndry(iter._segBndry){};
        virtual ~iterator() {};
        virtual bool              operator==(const iterator& iter) const {return this->_itor == iter._itor;};
        virtual bool              operator!=(const iterator& iter) const {return this->_itor != iter._itor;};
        // FIX: operator*() should return a const reference, but it won't compile that way, because _ex() returns const value_type
        virtual const value_type  operator*() const {return _ex(*(this->_itor));};
        virtual iterator   operator++() {
          this->_sequence->next(this->_itor, this->_segBndry);
          return *this;
        };
        virtual iterator   operator++(int n) {iterator tmp(*this); ++(*this); return tmp;};
      };// class iterator
    protected:
      //
      index_type      *_index;
      //
      outer_filter_type   _outer_filter;
      inner_filter_type   _inner_filter;
      //
      outer_key_extractor_type _okex;
      inner_key_extractor_type _ikex;
    public:
      //
      // Basic interface
      //
      FilteredIndexSequence() : XObject(), _index(NULL), _outer_filter(NULL), _inner_filter(NULL) {};
      FilteredIndexSequence(index_type *index, const outer_filter_type& outer_filter, const inner_filter_type& inner_filter) : 
        XObject(), _index(index), _outer_filter(outer_filter), _inner_filter(inner_filter){};
      FilteredIndexSequence(const FilteredIndexSequence& seq) : 
        XObject(seq), _index(seq._index), _outer_filter(seq._outer_filter), _inner_filter(seq._inner_filter) {};
      virtual ~FilteredIndexSequence() {};
      // 
      void copy(const FilteredIndexSequence& seq, FilteredIndexSequence cseq) {
        cseq._index = seq._index; 
        cseq._inner_filter = seq._inner_filter;
        cseq._outer_filter = seq._outer_filter;
      };
      FilteredIndexSequence& operator=(const FilteredIndexSequence& seq) {
        copy(seq,*this); return *this;
      };
      void reset(index_type *index, const inner_filter_type& inner_filter, const outer_filter_type& outer_filter) {
        this->_index         = index;
        this->_inner_filter  = inner_filter;
        this->_outer_filter  = outer_filter;
      };
      //
      // Extended interface
      //
      virtual bool         
      empty() {return (this->begin() == this->end());};
      //
      virtual size_type  
      size()  {
        size_type sz = 0;
        for(iterator it = this->begin(); it != this->end(); it++) {
          ++sz;
        }
        return sz;
      };
      // 
      inner_filter_type& innerFilter(){return this->_inner_filter;};
      outer_filter_type& outerFilter(){return this->_outer_filter;};
      void setInnerFilter(const inner_filter_type& inner_filter) {this->_inner_filter = inner_filter;};
      void setOuterFilter(const outer_filter_type& outer_filter) {this->_outer_filter = outer_filter;};
      //
      #undef  __FUNCT__
      #define __FUNCT__ "begin"
      iterator begin() {
        if(this->debug()) {
          std::cout << std::endl << __CLASS__ << "::" << __FUNCT__ << ": ";
          std::cout << "outer filter: " << this->outerFilter() << ", ";
          //
          std::cout << "inner filter: " << this->innerFilter() << std::endl;
        }
        static itor_type itor;
//         // Determine the lower outer limit iterator
//         if(this->outerFilter().haveLow()) {
//           // ASSUMPTION: index ordering operator can compare against outer_key singleton
//           itor = this->_index->lower_bound(ALE::singleton<outer_key_type>(this->outerFilter().low()));
//         }
//         else {
//           itor = this->_index->begin();
//         }
//         // Now determine the inner lower limit and set the iterator to that limit within the first segment
//         if(this->innerFilter().haveLow()) {
//           // ASSUMPTION: index ordering operator can compare against (outer_key, inner_key) pairs
//           itor = this->_index->lower_bound(ALE::pair<outer_key_type, inner_key_type>(this->_okex(*itor),this->innerFilter().low()));
//         }
//         else {
//           // the itor is already in the right place: nothing to do
//         }  
        // ASSUMPTION: index ordering operator can compare against (outer_key, inner_key) pairs
        static itor_type segBndry;
        // Segment boundary set to just above the current (outer_key, inner_key) pair.
        //segBndry = this->_index->upper_bound(ALE::pair<outer_key_type, inner_key_type>(this->_okex(*itor),this->_ikex(*itor)));
        itor = this->innerFilter().begin(this->outerFilter().begin(), this->outerFilter());
        segBndry = this->innerFilter().end(itor,this->outerFilter());
        if(this->debug()){
          //
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "*itor " << *itor; 
          std::cout << ", (okey, ikey): (" << this->_okex(*itor) << ", " << this->_ikex(*itor) << ") " << std::endl;
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "*segBndry " << *segBndry;
          std::cout << ", (okey, ikey): (" << this->_okex(*segBndry) << ", " << this->_ikex(*segBndry) << ") " << std::endl;
        }
        return iterator(this, itor, segBndry);
      }; // begin()
      //
      #undef  __FUNCT__
      #define __FUNCT__ "next"
      void next(itor_type& itor, itor_type& segBndry) {
        if(this->debug()) {
          std::cout << std::endl << __CLASS__ << "::" << __FUNCT__ << ": ";
          std::cout << "outer filter: " << this->outerFilter() << ", ";
          //
          std::cout << "inner filter: " << this->innerFilter() << std::endl;
          //
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "starting with *itor " << *itor; 
          std::cout << ", (okey, ikey): (" << this->_okex(*itor) << ", " << this->_ikex(*itor) << ") " << std::endl;
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "starting with *segBndry " << *segBndry;
          std::cout << ", (okey, ikey): (" << this->_okex(*segBndry) << ", " << this->_ikex(*segBndry) << ") " << std::endl;
        }
        outer_key_type olow;
        inner_key_type ilow;
        // If iteration is to be strided to skip RemainderKeys, we advance directly to the segment boundary.
        // Effectively, we iterate over segments.
        if(Strided) {
          if(this->debug()) {
            std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "inner key strided " << std::endl;
          }
          // Advance itor to the segment boundary
          itor = segBndry;
          // ASSUMPTION: index ordering operator can compare against (outer_key, inner_key) pairs
          olow = this->_okex(*itor);
          ilow = this->_ikex(*itor);
          // Compute the new segment's boundary
          segBndry = this->_index->upper_bound(ALE::pair<outer_key_type, inner_key_type>(olow,ilow));
        }// Strided
        // Otherwise, we iterate *within* a segment until its end is reached; then the following segment is started.
        else {
          if(this->debug()) {
            std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "inner key not strided " << std::endl;
          }
          // See if our advance would lead to breaching the segment boundary:
          itor_type tmp_itor = ++(itor);
          if(tmp_itor != segBndry) { 
            // if not breached the segment boundary, simply use the advanced iterator
            itor = tmp_itor;
          }
          else {
            // Obtain the current outer key from itor:
            olow = this->_okex(*itor);
            // Compute the lower boundary of the new segment
            // ASSUMPTION: index ordering operator can compare against outer_keys
            itor = this->_index->upper_bound(ALE::singleton<outer_key_type>(olow));
            // Extract the new outer key
            olow = this->_okex(*itor);
            // Now determine the inner lower limit and set the iterator to that limit within the new segment
            if(this->innerFilter().haveLow()) {
              ilow = this->innerFilter().low();
              // ASSUMPTION: index ordering operator can compare against (outer_key, inner_key) pairs
              itor = this->_index->lower_bound(ALE::pair<outer_key_type, inner_key_type>(olow,ilow));
            }
            else {
              // the itor is already in the right place; need to extract the ilow key
              ilow = this->_ikex(*itor);
            }
            // Finally, compute the new segment's boundary
            // ASSUMPTION: index ordering operator can compare against (outer_key, inner_key) pairs
            segBndry = this->_index->upper_bound(ALE::pair<outer_key_type, inner_key_type>(olow,ilow));
          }
        }// not Strided
        if(this->debug()) {
          //
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "new *itor " << *itor; 
          std::cout << ", (okey, ikey): (" << this->_okex(*itor) << ", " << this->_ikex(*itor) << ") " << std::endl;
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "new *segBndry " << *segBndry;
          std::cout << ", (okey, ikey): (" << this->_okex(*segBndry) << ", " << this->_ikex(*segBndry) << ") " << std::endl;
        }
      };// next()
      //
      #undef  __FUNCT__
      #define __FUNCT__ "end"
      iterator end() {
        if(this->debug()) {
          std::cout << std::endl << __CLASS__ << "::" << __FUNCT__ << ": ";
          std::cout << "outer filter: " << this->outerFilter() << ", ";
          //
          std::cout << "inner filter: " << this->innerFilter() << std::endl;
        }
        static itor_type itor;
        static ritor_type ritor;
        // Determine the upper outer limit
        static outer_key_type ohigh;
        if(this->outerFilter().haveHigh()) {
          ohigh = this->outerFilter().high();
        }
        else {
          ritor = this->_index->rbegin();
          ohigh = this->_okex(*ritor);
        }
        // Determine the inner outer limit
        static inner_key_type ihigh;
        if(this->innerFilter().haveHigh()) {
          ihigh = this->innerFilter().high();
          // ASSUMPTION: index ordering operator can compare against (outer_key, inner_key) pairs
          itor = this->_index->upper_bound(ALE::pair<outer_key_type, inner_key_type>(ohigh,ihigh));
        }
        else {
          // ASSUMPTION: index ordering operator can compare against outer_key singletons.
          itor = this->_index->upper_bound(ALE::singleton<outer_key_type>(ohigh));
        }
        // use segBndry == itor
        if(this->debug()){
          //
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "*itor " << *itor; 
          std::cout << ", (okey, ikey): (" << this->_okex(*itor) << ", " << this->_ikex(*itor) << ") " << std::endl;
          std::cout << __CLASS__ << "::" << __FUNCT__ << ": " << "*segBndry == *itor";
        }
        return iterator(this, itor, itor); 
      };// end()
      //
      virtual bool contains(const outer_key_type& ok, const inner_key_type& ik) {
        // FIX: This has to be implemented correctly, using the index ordering operator.
        //return (this->_index->find(ALE::pair<outer_key_type,inner_key_type>(ok,ik)) != this->_index->end());
        return true;
      };
     //
      template<typename ostream_type>
      void view(ostream_type& os, const char* label = NULL){
        if(label != NULL) {
          os << "Viewing " << label << " sequence:" << std::endl;
        } 
        os << "[";
        for(iterator i = this->begin(); i != this->end(); i++) {
          os << " "<< *i;
        }
        os << " ]" << std::endl;
      };
    };// class FilteredIndexSequence    
  }; // namespace XSifterDef
  
  //
  // XSifter definition
  template<typename Arrow_, 
           typename ArrowSupportOrder_= XSifterDef::TargetColorOrder<Arrow_>, 
           typename ArrowConeOrder_   = XSifterDef::SourceColorOrder<Arrow_>, 
           typename Predicate_ = int, typename PredicateOrder_ = std::less<Predicate_> >
  struct XSifter : XObject { // struct XSifter
    //
    // Encapsulated types
    //
    typedef Arrow_                           arrow_type;
    typedef typename arrow_type::source_type source_type;
    typedef typename arrow_type::target_type target_type;
    typedef typename arrow_type::color_type  color_type;
    //
    // Internal types
    //
    // Predicates and Rec
    typedef Predicate_                       predicate_type;
    typedef PredicateOrder_                  predicate_order_type;
    struct Rec : public arrow_type {
    public:
      //
      // Re-export typedefs
      //
      typedef typename arrow_type::source_type        source_type;
      typedef typename arrow_type::target_type        target_type;
      typedef typename arrow_type::color_type         color_type;
    public:
      // Predicate stored alongside the arrow data
      predicate_type _predicate;
      // Basic interface
      Rec(const arrow_type& a) : arrow_type(a) {};
      Rec(const arrow_type& a, const predicate_type& p) : arrow_type(a), _predicate(p) {};
      // Extended interface
      predicate_type predicate() const{return this->_predicate;};
      source_type    source() const {return this->arrow_type::source();};
      target_type    target() const {return this->arrow_type::target();};
      // Printing
      friend std::ostream& operator<<(std::ostream& os, const Rec& r) {
        os << "[" << (arrow_type)r << "]<" << r._predicate << ">";
        return os;
      }

      // Modifier objects
      struct predicateChanger {
        predicateChanger(const predicate_type& newPredicate) : _newPredicate(newPredicate) {};
        void operator()(Rec& r) { r._predicate = this->_newPredicate;}
      private:
        const predicate_type _newPredicate;
      };
    };// struct Rec
    //
    typedef Rec                              rec_type;
    //
    // Compound orders are assembled here
    //
    typedef std::less<typename rec_type::source_type> source_order_type; 
    typedef std::less<typename rec_type::target_type> target_order_type;
    //
    // Rec 'downward' order type: first order by predicate, then source, then target, etc (Support order)
    struct downward_order_type : public 
    XSifterDef::RecKeyXXXOrder<rec_type, 
                              typename ::boost::multi_index::const_mem_fun<rec_type, predicate_type, &rec_type::predicate>, 
                              predicate_order_type, 
                              XSifterDef::RecKeyXXXOrder<rec_type,
                                                        ::boost::multi_index::const_mem_fun<rec_type, typename rec_type::source_type, &rec_type::source>,
                                                         source_order_type, ArrowSupportOrder_> > {};
    
    //
    // Rec 'upward' order type: first order by predicate, then target, then source, etc (Cone order)
    struct upward_order_type : public 
    XSifterDef::RecKeyXXXOrder<rec_type, 
                              typename ::boost::multi_index::const_mem_fun<rec_type,predicate_type, &rec_type::predicate>, 
                              predicate_order_type,
                              XSifterDef::RecKeyXXXOrder<rec_type,
                                                        ::boost::multi_index::const_mem_fun<rec_type, typename rec_type::target_type, &rec_type::target>,
                                                         target_order_type, ArrowConeOrder_> >
    {};
    
    //
    // Index tags
    //
    struct                                   DownwardTag{};
    struct                                   UpwardTag{};
    
    // Rec set type
    typedef ::boost::multi_index::multi_index_container< 
      rec_type,
      ::boost::multi_index::indexed_by< 
        ::boost::multi_index::ordered_non_unique<
          ::boost::multi_index::tag<DownwardTag>, ::boost::multi_index::identity<rec_type>, downward_order_type
        >,
        ::boost::multi_index::ordered_non_unique<
          ::boost::multi_index::tag<UpwardTag>, ::boost::multi_index::identity<rec_type>, upward_order_type
        > 
      >,
      ALE_ALLOCATOR<rec_type> > 
    rec_set_type;
    //
    // Index types
    typedef typename ::boost::multi_index::index<rec_set_type, UpwardTag>::type   upward_index_type;
    typedef typename ::boost::multi_index::index<rec_set_type, DownwardTag>::type downward_index_type;
    //
    // Sequence types
    template <typename Index_, 
              typename OuterFilter_, typename InnerFilter_, typename ValueExtractor_, bool Strided = false>
    class ArrowSequence : 
      public XSifterDef::FilteredIndexSequence<Index_, OuterFilter_, InnerFilter_, ValueExtractor_, Strided> {
      // ArrowSequence extends FilteredIndexSequence with extra iterator methods.
    public:
      typedef XSifterDef::FilteredIndexSequence<Index_, OuterFilter_, InnerFilter_, ValueExtractor_, Strided> super;
      typedef XSifter                                                                                                               container_type;
      typedef typename super::index_type                                                                                            index_type;
      typedef typename super::outer_filter_type                                                                                     outer_filter_type;
      typedef typename super::inner_filter_type                                                                                     inner_filter_type;
      typedef typename super::outer_key_type                                                                                        outer_key_type;
      typedef typename super::inner_key_type                                                                                        inner_key_type;
      
      // Need to extend the inherited iterators to be able to extract arrow color
      class iterator : public super::iterator {
      public:
        iterator() : super::iterator() {};
        iterator(const typename super::iterator& super_iter) : super::iterator(super_iter) {};
        virtual const source_type& source() const {return this->_itor->_source;};
        virtual const color_type&  color()  const {return this->_itor->_color;};
        virtual const target_type& target() const {return this->_itor->_target;};
        virtual const arrow_type&  arrow()  const {return *(this->_itor);};
      };
    protected:
      container_type *_container;
    public:
      //
      // Basic ArrowSequence interface
      //
      ArrowSequence() : super(), _container(NULL) {};
      ArrowSequence(const ArrowSequence& seq) : super(seq), _container(seq._container) {};
      ArrowSequence(container_type *container, index_type *index, const outer_filter_type& outer_filter, const inner_filter_type& inner_filter) : 
        super(index, outer_filter, inner_filter), _container(container) {};
      virtual ~ArrowSequence() {};
      void copy(const ArrowSequence& seq, ArrowSequence& cseq) {
        super::copy(seq,cseq);
        cseq._container = seq._container;
      };
      void reset(container_type *container, index_type *index, const outer_filter_type& outer_filter, const inner_filter_type& inner_filter) {
        this->super::reset(index, outer_filter, inner_filter);
        this->_container = container;
      };
      ArrowSequence& operator=(const ArrowSequence& seq) {
        copy(seq,*this); return *this;
      };
      //
      // Extended ArrowSequence interface
      //
      virtual iterator begin() {
        return this->super::begin();
      };
      //
      virtual iterator end() {
        return this->super::end();
      };
      //
      template<typename ostream_type>
      void view(ostream_type& os, const bool& useColor = false, const char* label = NULL){
        if(label != NULL) {
          os << "Viewing " << label << " sequence:" << std::endl;
        } 
        os << "[";
        for(iterator i = this->begin(); i != this->end(); i++) {
          os << " (" << *i;
          if(useColor) {
            os << "," << i.color();
          }
          os  << ")";
        }
        os << " ]" << std::endl;
      };
      void addArrow(const arrow_type& a) {
        this->_container->addArrow(a);
      };
      //
    };// class ArrowSequence    

    //
    // FilterManager types
    //
    typedef XSifterDef::DummyFilterManager<upward_index_type, ::boost::multi_index::const_mem_fun<rec_type, predicate_type, &rec_type::predicate> >
    UpwardPredicateFilterManager;
    //
    typedef XSifterDef::DummyFilterManager<upward_index_type, ::boost::multi_index::const_mem_fun<rec_type, target_type, &rec_type::target> >
    UpwardTargetFilterManager;
    //
    // Specialized sequence types
    //
    typedef ArrowSequence<typename ::boost::multi_index::index<rec_set_type, UpwardTag>::type,
                          ALE::XSifterDef::RangeFilter<UpwardPredicateFilterManager>, 
                          ALE::XSifterDef::RangeFilter<UpwardTargetFilterManager>,
                          ::boost::multi_index::const_mem_fun<rec_type, target_type, &rec_type::target>, 
                          true>                                                       
    BaseSequence;

    typedef ArrowSequence<typename ::boost::multi_index::index<rec_set_type, UpwardTag>::type,
                          ALE::XSifterDef::RangeFilter<UpwardPredicateFilterManager >,
                          ALE::XSifterDef::RangeFilter<UpwardTargetFilterManager>,
                          ::boost::multi_index::const_mem_fun<rec_type, source_type, &rec_type::source> >     
    ConeSequence;
    //
    // Basic interface
    //
    XSifter(const MPI_Comm comm, int debug = 0) : // FIXIT: Should really inherit from XParallelObject
      XObject(debug), _rec_set(), 
      _upward_predicate_filter_manager(::boost::multi_index::get<UpwardTag>(_rec_set)),
      _upward_target_filter_manager(::boost::multi_index::get<UpwardTag>(_rec_set)){};
    //
    // Extended interface
    //
    void addArrow(const arrow_type& a) {
#ifdef ALE_USE_DEBUGGING
      rec_type r(a);
      this->_rec_set.insert(r);
#else
      this->_rec_set.insert(rec_type(a));
#endif
    };
    void cone(const target_type& t, ConeSequence& seq) {
      seq.reset(this, &::boost::multi_index::get<UpwardTag>(this->_rec_set),
                XSifterDef::RangeFilter<UpwardPredicateFilterManager>(), XSifterDef::RangeFilter<UpwardTargetFilterManager>(t,t));
    };
//     ConeSequence& cone(const target_type& t) {
//       static ConeSequence cseq;
// #ifdef ALE_USE_DEBUGGING
//       cseq.debug(this->debug());
// #endif
//       this->cone(t,cseq);
//       return cseq;
//     };
  ConeSequence cone(const target_type& t) {
      return ConeSequence(this, &::boost::multi_index::get<UpwardTag>(this->_rec_set),
                XSifterDef::RangeFilter<UpwardPredicateFilterManager>(), XSifterDef::RangeFilter<UpwardTargetFilterManager>(t,t));
  };
    void base(BaseSequence& seq) {
      seq.reset(this, &::boost::multi_index::get<UpwardTag>(this->_rec_set), 
                XSifterDef::RangeFilter<UpwardPredicateFilterManager>(&this->_upward_predicate_filter_manager), 
                XSifterDef::RangeFilter<UpwardTargetFilterManager>(&this->_upward_target_filter_manager));
    };
//     BaseSequence& base() {
//       static BaseSequence bseq;
// #ifdef ALE_USE_DEBUGGING
//       bseq.debug(this->debug());
// #endif
//       this->base(bseq);
//       return bseq;
//     };
    //
    BaseSequence base() {
      return BaseSequence(this, &::boost::multi_index::get<UpwardTag>(this->_rec_set), 
                XSifterDef::RangeFilter<UpwardPredicateFilterManager>(&this->_upward_predicate_filter_manager), 
                XSifterDef::RangeFilter<UpwardTargetFilterManager>(&this->_upward_target_filter_manager));
    };
    //
    template<typename ostream_type>
    void view(ostream_type& os, const char* label = NULL){
      if(label != NULL) {
        os << "Viewing " << label << " XSifter (debug: " << this->debug() << "): " << std::endl;
      } 
      else {
        os << "Viewing a XSifter (debug: " << this->debug() << "): " << std::endl;
      } 
      upward_index_type&   upward_index   = ::boost::multi_index::get<UpwardTag>(this->_rec_set);
      downward_index_type& downward_index = ::boost::multi_index::get<DownwardTag>(this->_rec_set);
      os << "Downward index: (";
        for(typename downward_index_type::iterator itor = downward_index.begin(); itor != downward_index.end(); ++itor) {
          os << *itor << " ";
        }
      os << ")" << std::endl;
      os << "Upward index: (";
        for(typename upward_index_type::iterator itor = upward_index.begin(); itor != upward_index.end(); ++itor) {
          os << *itor << " ";
        }
      os << ")" << std::endl;
    };
  protected:
    // set of arrow records
    rec_set_type _rec_set;
    // index filter managers
    UpwardPredicateFilterManager _upward_predicate_filter_manager;
    UpwardTargetFilterManager    _upward_target_filter_manager;
  }; // class XSifter


} // namespace ALE

#endif
