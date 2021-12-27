/*
      Objects which encapsulate discretizations+continuum residuals
*/
#if !defined(PETSCDS_H)
#define PETSCDS_H
#include <petscfe.h>
#include <petscfv.h>
#include <petscdstypes.h>

PETSC_EXTERN PetscClassId PETSCWEAKFORM_CLASSID;

PETSC_EXTERN PetscErrorCode PetscWeakFormCreate(MPI_Comm, PetscWeakForm *);
PETSC_EXTERN PetscErrorCode PetscWeakFormDestroy(PetscWeakForm *);
PETSC_EXTERN PetscErrorCode PetscWeakFormView(PetscWeakForm, PetscViewer);
PETSC_EXTERN PetscErrorCode PetscWeakFormCopy(PetscWeakForm, PetscWeakForm);
PETSC_EXTERN PetscErrorCode PetscWeakFormClear(PetscWeakForm);
PETSC_EXTERN PetscErrorCode PetscWeakFormGetNumFields(PetscWeakForm, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscWeakFormSetNumFields(PetscWeakForm, PetscInt);
PETSC_EXTERN PetscErrorCode PetscFormKeySort(PetscInt, PetscFormKey[]);
PETSC_EXTERN PetscErrorCode PetscWeakFormRewriteKeys(PetscWeakForm, DMLabel, PetscInt, const PetscInt[]);
PETSC_EXTERN PetscErrorCode PetscWeakFormReplaceLabel(PetscWeakForm, DMLabel);
PETSC_EXTERN PetscErrorCode PetscWeakFormClearIndex(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscWeakFormKind, PetscInt);

PETSC_EXTERN PetscErrorCode PetscWeakFormGetObjective(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt *,
                                                      void (***)(PetscInt, PetscInt, PetscInt,
                                                                 const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                 const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                 PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormAddObjective(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetObjective(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                      void (**)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormGetIndexObjective(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                      void (**)(PetscInt, PetscInt, PetscInt,
                                                                 const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                 const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                 PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetIndexObjective(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormGetResidual(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormAddResidual(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetResidual(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetIndexResidual(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormHasJacobian(PetscWeakForm, PetscBool *);
PETSC_EXTERN PetscErrorCode PetscWeakFormGetJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormAddJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetIndexJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormHasJacobianPreconditioner(PetscWeakForm, PetscBool *);
PETSC_EXTERN PetscErrorCode PetscWeakFormGetJacobianPreconditioner(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormAddJacobianPreconditioner(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetJacobianPreconditioner(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetIndexJacobianPreconditioner(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormHasDynamicJacobian(PetscWeakForm, PetscBool *);
PETSC_EXTERN PetscErrorCode PetscWeakFormGetDynamicJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt *,
                                                     void (***)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormAddDynamicJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetDynamicJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (**)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetIndexDynamicJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                     PetscInt,
                                                     void (*)(PetscInt, PetscInt, PetscInt,
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormGetBdResidual(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                       PetscInt *,
                                                       void (***)(PetscInt, PetscInt, PetscInt,
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt *,
                                                       void (***)(PetscInt, PetscInt, PetscInt,
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormAddBdResidual(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetBdResidual(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                       PetscInt,
                                                       void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetIndexBdResidual(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                       PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormHasBdJacobian(PetscWeakForm, PetscBool *);
PETSC_EXTERN PetscErrorCode PetscWeakFormGetBdJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                       PetscInt *,
                                                       void (***)(PetscInt, PetscInt, PetscInt,
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt *,
                                                       void (***)(PetscInt, PetscInt, PetscInt,
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt *,
                                                       void (***)(PetscInt, PetscInt, PetscInt,
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt *,
                                                       void (***)(PetscInt, PetscInt, PetscInt,
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormAddBdJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetBdJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                       PetscInt,
                                                       void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetIndexBdJacobian(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                       PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormHasBdJacobianPreconditioner(PetscWeakForm, PetscBool *);
PETSC_EXTERN PetscErrorCode PetscWeakFormGetBdJacobianPreconditioner(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                       PetscInt *,
                                                       void (***)(PetscInt, PetscInt, PetscInt,
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt *,
                                                       void (***)(PetscInt, PetscInt, PetscInt,
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt *,
                                                       void (***)(PetscInt, PetscInt, PetscInt,
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt *,
                                                       void (***)(PetscInt, PetscInt, PetscInt,
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                  PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormAddBdJacobianPreconditioner(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetBdJacobianPreconditioner(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                       PetscInt,
                                                       void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetIndexBdJacobianPreconditioner(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt, PetscInt,
                                                       PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                       PetscInt,
                                                       void (*)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscWeakFormGetRiemannSolver(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                          PetscInt *,
                                                          void (***)(PetscInt, PetscInt, const PetscReal[], const PetscReal[], const PetscScalar[], const PetscScalar[], PetscInt, const PetscScalar[], PetscScalar[], void *));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetRiemannSolver(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                          PetscInt,
                                                          void (**)(PetscInt, PetscInt, const PetscReal[], const PetscReal[], const PetscScalar[], const PetscScalar[], PetscInt, const PetscScalar[], PetscScalar[], void *));
PETSC_EXTERN PetscErrorCode PetscWeakFormSetIndexRiemannSolver(PetscWeakForm, DMLabel, PetscInt, PetscInt, PetscInt,
                                                          PetscInt,
                                                          void (*)(PetscInt, PetscInt, const PetscReal[], const PetscReal[], const PetscScalar[], const PetscScalar[], PetscInt, const PetscScalar[], PetscScalar[], void *));

PETSC_EXTERN PetscErrorCode PetscDSInitializePackage(void);

PETSC_EXTERN PetscClassId PETSCDS_CLASSID;

/*J
  PetscDSType - String with the name of a PETSc discrete system

  Level: beginner

.seealso: PetscDSSetType(), PetscDS
J*/
typedef const char *PetscDSType;
#define PETSCDSBASIC "basic"

typedef enum {PETSC_DISC_NONE, PETSC_DISC_FE, PETSC_DISC_FV} PetscDiscType;

typedef void (*PetscPointFunc)(PetscInt, PetscInt, PetscInt,
                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                               PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]);
typedef void (*PetscPointJac)(PetscInt, PetscInt, PetscInt,
                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                              const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                              PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]);
typedef void (*PetscBdPointFunc)(PetscInt, PetscInt, PetscInt,
                                 const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                 const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                 PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]);
typedef void (*PetscBdPointJac)(PetscInt, PetscInt, PetscInt,
                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]);
typedef void (*PetscRiemannFunc)(PetscInt, PetscInt, const PetscReal[], const PetscReal[], const PetscScalar[], const PetscScalar[], PetscInt, const PetscScalar[], PetscScalar[], void *);
typedef PetscErrorCode (*PetscSimplePointFunc)(PetscInt, PetscReal, const PetscReal[], PetscInt, PetscScalar[], void *);

PETSC_EXTERN PetscFunctionList PetscDSList;
PETSC_EXTERN PetscErrorCode PetscDSCreate(MPI_Comm, PetscDS *);
PETSC_EXTERN PetscErrorCode PetscDSDestroy(PetscDS *);
PETSC_EXTERN PetscErrorCode PetscDSSetType(PetscDS, PetscDSType);
PETSC_EXTERN PetscErrorCode PetscDSGetType(PetscDS, PetscDSType *);
PETSC_EXTERN PetscErrorCode PetscDSSetUp(PetscDS);
PETSC_EXTERN PetscErrorCode PetscDSSetFromOptions(PetscDS);
PETSC_EXTERN PetscErrorCode PetscDSViewFromOptions(PetscDS,PetscObject,const char[]);

PETSC_EXTERN PetscErrorCode PetscDSView(PetscDS,PetscViewer);
PETSC_EXTERN PetscErrorCode PetscDSRegister(const char [], PetscErrorCode (*)(PetscDS));
PETSC_EXTERN PetscErrorCode PetscDSRegisterDestroy(void);

PETSC_EXTERN PetscErrorCode PetscDSGetHeightSubspace(PetscDS, PetscInt, PetscDS *);
PETSC_EXTERN PetscErrorCode PetscDSGetSpatialDimension(PetscDS, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSGetCoordinateDimension(PetscDS, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSSetCoordinateDimension(PetscDS, PetscInt);
PETSC_EXTERN PetscErrorCode PetscDSGetHybrid(PetscDS, PetscBool *);
PETSC_EXTERN PetscErrorCode PetscDSSetHybrid(PetscDS, PetscBool);
PETSC_EXTERN PetscErrorCode PetscDSGetNumFields(PetscDS, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSGetTotalDimension(PetscDS, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSGetTotalComponents(PetscDS, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSGetFieldIndex(PetscDS, PetscObject, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSGetFieldSize(PetscDS, PetscInt, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSGetFieldOffset(PetscDS, PetscInt, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSGetDimensions(PetscDS, PetscInt *[]);
PETSC_EXTERN PetscErrorCode PetscDSGetComponents(PetscDS, PetscInt *[]);
PETSC_EXTERN PetscErrorCode PetscDSGetComponentOffset(PetscDS, PetscInt, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSGetComponentOffsets(PetscDS, PetscInt *[]);
PETSC_EXTERN PetscErrorCode PetscDSGetComponentDerivativeOffsets(PetscDS, PetscInt *[]);

PETSC_EXTERN PetscErrorCode PetscDSGetWeakForm(PetscDS, PetscWeakForm *);
PETSC_EXTERN PetscErrorCode PetscDSSetWeakForm(PetscDS, PetscWeakForm);
PETSC_EXTERN PetscErrorCode PetscDSGetDiscretization(PetscDS, PetscInt, PetscObject *);
PETSC_EXTERN PetscErrorCode PetscDSSetDiscretization(PetscDS, PetscInt, PetscObject);
PETSC_EXTERN PetscErrorCode PetscDSAddDiscretization(PetscDS, PetscObject);
PETSC_EXTERN PetscErrorCode PetscDSGetQuadrature(PetscDS, PetscQuadrature*);
PETSC_EXTERN PetscErrorCode PetscDSGetImplicit(PetscDS, PetscInt, PetscBool*);
PETSC_EXTERN PetscErrorCode PetscDSSetImplicit(PetscDS, PetscInt, PetscBool);
PETSC_EXTERN PetscErrorCode PetscDSGetJetDegree(PetscDS, PetscInt, PetscInt*);
PETSC_EXTERN PetscErrorCode PetscDSSetJetDegree(PetscDS, PetscInt, PetscInt);
PETSC_EXTERN PetscErrorCode PetscDSGetConstants(PetscDS, PetscInt *, const PetscScalar *[]);
PETSC_EXTERN PetscErrorCode PetscDSSetConstants(PetscDS, PetscInt, PetscScalar[]);
PETSC_EXTERN PetscErrorCode PetscDSGetObjective(PetscDS, PetscInt,
                                                void (**)(PetscInt, PetscInt, PetscInt,
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSSetObjective(PetscDS, PetscInt,
                                                void (*)(PetscInt, PetscInt, PetscInt,
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSGetResidual(PetscDS, PetscInt,
                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSSetResidual(PetscDS, PetscInt,
                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSGetRHSResidual(PetscDS, PetscInt,
                                                  void (**)(PetscInt, PetscInt, PetscInt,
                                                            const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                            const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                            PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                  void (**)(PetscInt, PetscInt, PetscInt,
                                                            const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                            const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                            PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSSetRHSResidual(PetscDS, PetscInt,
                                                  void (*)(PetscInt, PetscInt, PetscInt,
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                  void (*)(PetscInt, PetscInt, PetscInt,
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSHasJacobian(PetscDS, PetscBool *);
PETSC_EXTERN PetscErrorCode PetscDSGetJacobian(PetscDS, PetscInt, PetscInt,
                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSSetJacobian(PetscDS, PetscInt, PetscInt,
                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSUseJacobianPreconditioner(PetscDS, PetscBool);
PETSC_EXTERN PetscErrorCode PetscDSHasJacobianPreconditioner(PetscDS, PetscBool *);
PETSC_EXTERN PetscErrorCode PetscDSGetJacobianPreconditioner(PetscDS, PetscInt, PetscInt,
                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                         PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSSetJacobianPreconditioner(PetscDS, PetscInt, PetscInt,
                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                        PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSHasDynamicJacobian(PetscDS, PetscBool *);
PETSC_EXTERN PetscErrorCode PetscDSGetDynamicJacobian(PetscDS, PetscInt, PetscInt,
                                                      void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (**)(PetscInt, PetscInt, PetscInt,
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSSetDynamicJacobian(PetscDS, PetscInt, PetscInt,
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                      void (*)(PetscInt, PetscInt, PetscInt,
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                               PetscReal, PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSGetRiemannSolver(PetscDS, PetscInt,
                                                    void (**)(PetscInt, PetscInt, const PetscReal[], const PetscReal[], const PetscScalar[], const PetscScalar[], PetscInt, const PetscScalar[], PetscScalar[], void *));
PETSC_EXTERN PetscErrorCode PetscDSSetRiemannSolver(PetscDS, PetscInt,
                                                    void (*)(PetscInt, PetscInt, const PetscReal[], const PetscReal[], const PetscScalar[], const PetscScalar[], PetscInt, const PetscScalar[], PetscScalar[], void *));
PETSC_EXTERN PetscErrorCode PetscDSGetUpdate(PetscDS, PetscInt,
                                             void (**)(PetscInt, PetscInt, PetscInt,
                                                       const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                       const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                       PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSSetUpdate(PetscDS, PetscInt,
                                             void (*)(PetscInt, PetscInt, PetscInt,
                                                      const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                      const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                      PetscReal, const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSGetContext(PetscDS, PetscInt, void *);
PETSC_EXTERN PetscErrorCode PetscDSSetContext(PetscDS, PetscInt, void *);
PETSC_EXTERN PetscErrorCode PetscDSGetBdResidual(PetscDS, PetscInt,
                                                 void (**)(PetscInt, PetscInt, PetscInt,
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                 void (**)(PetscInt, PetscInt, PetscInt,
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSSetBdResidual(PetscDS, PetscInt,
                                                 void (*)(PetscInt, PetscInt, PetscInt,
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                 void (*)(PetscInt, PetscInt, PetscInt,
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSHasBdJacobian(PetscDS, PetscBool *);
PETSC_EXTERN PetscErrorCode PetscDSGetBdJacobian(PetscDS, PetscInt, PetscInt,
                                                 void (**)(PetscInt, PetscInt, PetscInt,
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                 void (**)(PetscInt, PetscInt, PetscInt,
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                 void (**)(PetscInt, PetscInt, PetscInt,
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                 void (**)(PetscInt, PetscInt, PetscInt,
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                           PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSSetBdJacobian(PetscDS, PetscInt, PetscInt,
                                                 void (*)(PetscInt, PetscInt, PetscInt,
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                 void (*)(PetscInt, PetscInt, PetscInt,
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                 void (*)(PetscInt, PetscInt, PetscInt,
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                 void (*)(PetscInt, PetscInt, PetscInt,
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                          PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSHasBdJacobianPreconditioner(PetscDS, PetscBool *);
PETSC_EXTERN PetscErrorCode PetscDSGetBdJacobianPreconditioner(PetscDS, PetscInt, PetscInt,
                                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                         PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                         PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                         PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                               void (**)(PetscInt, PetscInt, PetscInt,
                                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                         const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                         PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSSetBdJacobianPreconditioner(PetscDS, PetscInt, PetscInt,
                                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                        PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                        PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                        PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]),
                                                               void (*)(PetscInt, PetscInt, PetscInt,
                                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                        const PetscInt[], const PetscInt[], const PetscScalar[], const PetscScalar[], const PetscScalar[],
                                                                        PetscReal, PetscReal, const PetscReal[], const PetscReal[], PetscInt, const PetscScalar[], PetscScalar[]));
PETSC_EXTERN PetscErrorCode PetscDSGetExactSolution(PetscDS, PetscInt, PetscErrorCode (**)(PetscInt, PetscReal, const PetscReal[], PetscInt, PetscScalar[], void *), void **);
PETSC_EXTERN PetscErrorCode PetscDSSetExactSolution(PetscDS, PetscInt, PetscErrorCode (*)(PetscInt, PetscReal, const PetscReal[], PetscInt, PetscScalar[], void *), void *);
PETSC_EXTERN PetscErrorCode PetscDSGetExactSolutionTimeDerivative(PetscDS, PetscInt, PetscErrorCode (**)(PetscInt, PetscReal, const PetscReal[], PetscInt, PetscScalar[], void *), void **);
PETSC_EXTERN PetscErrorCode PetscDSSetExactSolutionTimeDerivative(PetscDS, PetscInt, PetscErrorCode (*)(PetscInt, PetscReal, const PetscReal[], PetscInt, PetscScalar[], void *), void *);
PETSC_EXTERN PetscErrorCode PetscDSGetTabulation(PetscDS, PetscTabulation *[]);
PETSC_EXTERN PetscErrorCode PetscDSGetFaceTabulation(PetscDS, PetscTabulation *[]);
PETSC_EXTERN PetscErrorCode PetscDSGetEvaluationArrays(PetscDS, PetscScalar **, PetscScalar **, PetscScalar **);
PETSC_EXTERN PetscErrorCode PetscDSGetWeakFormArrays(PetscDS, PetscScalar **, PetscScalar **, PetscScalar **, PetscScalar **, PetscScalar **, PetscScalar **);
PETSC_EXTERN PetscErrorCode PetscDSGetWorkspace(PetscDS, PetscReal **, PetscScalar **, PetscScalar **, PetscScalar **, PetscScalar **);
PETSC_EXTERN PetscErrorCode PetscDSCopyConstants(PetscDS, PetscDS);
PETSC_EXTERN PetscErrorCode PetscDSCopyExactSolutions(PetscDS, PetscDS);
PETSC_EXTERN PetscErrorCode PetscDSCopyEquations(PetscDS, PetscDS);
PETSC_EXTERN PetscErrorCode PetscDSSelectDiscretizations(PetscDS, PetscInt, const PetscInt[], PetscDS);
PETSC_EXTERN PetscErrorCode PetscDSSelectEquations(PetscDS, PetscInt, const PetscInt[], PetscDS);
PETSC_EXTERN PetscErrorCode PetscDSAddBoundary(PetscDS, DMBoundaryConditionType, const char[], DMLabel, PetscInt, const PetscInt[], PetscInt, PetscInt, const PetscInt[], void (*)(void), void (*)(void), void *, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSAddBoundaryByName(PetscDS, DMBoundaryConditionType, const char[], const char[], PetscInt, const PetscInt[], PetscInt, PetscInt, const PetscInt[], void (*)(void), void (*)(void), void *, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSUpdateBoundary(PetscDS, PetscInt, DMBoundaryConditionType, const char[], DMLabel, PetscInt, const PetscInt[], PetscInt, PetscInt, const PetscInt[], void (*)(void), void (*)(void), void *);
PETSC_EXTERN PetscErrorCode PetscDSGetNumBoundary(PetscDS, PetscInt *);
PETSC_EXTERN PetscErrorCode PetscDSGetBoundary(PetscDS, PetscInt, PetscWeakForm *, DMBoundaryConditionType *, const char *[], DMLabel *, PetscInt *, const PetscInt *[], PetscInt *, PetscInt *, const PetscInt *[], void (**)(void), void (**)(void), void **);
PETSC_EXTERN PetscErrorCode PetscDSCopyBoundary(PetscDS, PetscInt, const PetscInt[], PetscDS);
PETSC_EXTERN PetscErrorCode PetscDSDestroyBoundary(PetscDS);

#endif
