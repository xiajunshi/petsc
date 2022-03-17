#!/usr/bin/env python
""" Configure PETSc and build and place still-required classic docs"""

import os
import errno
import subprocess
import shutil
import argparse

CLASSIC_DOCS_LOC = os.path.join(os.getcwd(), '_build_classic')
CLASSIC_DOCS_ARCH = 'arch-classic-docs'
HTMLMAP_DEFAULT_LOCATION = os.path.join(CLASSIC_DOCS_LOC, "docs", "manualpages", "htmlmap")

def main():
    """ Operations to provide data from the 'classic' PETSc docs system. """
    petsc_dir = os.path.abspath('..')
    _configure_minimal_petsc(petsc_dir, CLASSIC_DOCS_ARCH)
    _build_classic_docs_subset(petsc_dir, CLASSIC_DOCS_ARCH)


def clean():
    """ Clean up data generated by main() """
    classic_docs_arch_dir = os.path.abspath(os.path.join('..', CLASSIC_DOCS_ARCH))
    for directory in [CLASSIC_DOCS_LOC, classic_docs_arch_dir]:
        print('Removing %s' % directory)
        if os.path.isdir(directory):
            shutil.rmtree(directory)


def _mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc:
        if exc.errno == errno.EEXIST:
            pass
        else: raise


def _configure_minimal_petsc(petsc_dir, petsc_arch) -> None:
    if 'PETSC_ARCH' in os.environ: del os.environ['PETSC_ARCH']
    if 'MAKEFLAGS' in os.environ: del os.environ['MAKEFLAGS']
    configure = [
        './configure',
        '--with-mpi=0',
        '--with-blaslapack=0',
        '--with-fc=0',
        '--with-cxx=0',
        '--with-x=0',
        '--with-cmake=0',
        '--with-pthread=0',
        '--with-regexp=0',
        '--download-sowing',
        '--download-c2html',
        '--with-mkl_sparse_optimize=0',
        '--with-mkl_sparse=0',
        'PETSC_ARCH=' + petsc_arch,
    ]
    print('==================================================================')
    print('Performing a minimal PETSc (re-)configuration needed to build docs')
    print('PETSC_DIR=%s' % petsc_dir)
    print('PETSC_ARCH=%s' % petsc_arch)
    print('==================================================================')
    subprocess.run(configure, cwd=petsc_dir, check=True)
    return petsc_arch


def _build_classic_docs_subset(petsc_dir, petsc_arch):
    # Use htmlmap file as a sentinel
    htmlmap_filename = HTMLMAP_DEFAULT_LOCATION
    if os.path.isfile(htmlmap_filename):
        print('============================================')
        print('Assuming that the classic docs in %s are current' % CLASSIC_DOCS_LOC)
        print('To rebuild, manually run the following before re-making:\n  rm -rf %s' % CLASSIC_DOCS_LOC)
        print('============================================')
    else:
        command = ['make', 'alldoc12',
                   'PETSC_DIR=%s' % petsc_dir,
                   'PETSC_ARCH=%s' % petsc_arch,
                   'LOC=%s' % CLASSIC_DOCS_LOC]
        print('============================================')
        print('Building a subset of PETSc classic docs')
        print('PETSC_DIR=%s' % petsc_dir)
        print('PETSC_ARCH=%s' % petsc_arch)
        print(command)
        print('============================================')
        subprocess.run(command, cwd=petsc_dir, check=True)


def classic_docs_subdirs(stage):
    if stage == 'pre':
        return [os.path.join('docs', 'manualpages')]
    if stage == 'post':
        return ['include', 'src']
    raise Exception('Unrecognized stage %s' % stage)


def copy_classic_docs(outdir, stage):
    for subdir in classic_docs_subdirs(stage):
        source_dir = os.path.join(CLASSIC_DOCS_LOC, subdir)
        target_dir = os.path.join(outdir, subdir)
        print('Copying directory %s to %s' % (source_dir, target_dir))
        _mkdir_p(target_dir)
        for file in os.listdir(source_dir):
            source = os.path.join(source_dir, file)
            target = os.path.join(target_dir, file)
            if os.path.isdir(source):
                if os.path.isdir(target):
                    shutil.rmtree(target)
                shutil.copytree(source, target)
            else:
                shutil.copy(source, target)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--clean', '-c', action='store_true')
    args = parser.parse_args()

    if args.clean:
        clean()
    else:
        main()
