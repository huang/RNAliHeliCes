# ViennaRNA.spec
#
# Copyright (c) 2001 Ivo Hofacker, Peter Stadler, ivo@tbi.univie.ac.at
#
Name:           ViennaRNA
Version:        2.1.1.1
Release:        1%{?dist}
Summary:        RNA Secondary Structure Prediction and Comparison

Vendor:         Ivo Hofacker, TBI - University of Vienna
Packager:       Ronny Lorenz <ronny@tbi.univie.ac.at>

Group:          Applications/Engineering
License:        Free for non commercial use.
URL:            http://www.tbi.univie.ac.at/~ivo/RNA/
Source0:        http://www.tbi.univie.ac.at/~ronny/programs/%{name}-%{version}.tar.gz
BuildRoot:      %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)

BuildRequires:  perl gcc glibc-devel gd-devel info
Requires:       perl libstdc++ glibc gd info
Provides:       libRNA.a = %{version}-%{release}
Provides:       Kinfold

%define manifest %{_builddir}/%{name}-%{version}-%{release}.manifest

%description
The ViennaRNA package consists of a library and several standalone
programs for RNA secondary structure analysis. It includes algorithms
for predicting optimal and suboptimal secondary structures, base pair
probabilities and partition functions, for comparing secondary
structures, and the design of RNA sequences with a desired structure.

%prep
%setup -q

%build
%configure --with-cluster --without-forester --prefix=/usr/
cd Perl
perl Makefile.PL INSTALLDIRS=vendor
cd ..
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

# crude bugfix for info clash
rm -f $RPM_BUILD_ROOT/usr/share/info/dir

# build filelist the lazy way
rm -f %{manifest}
cd %{buildroot}
# crude sed bugfix due to man/info compression
find . -type f \
        | sed -e 's/^\.//' -e 's/\(.*\/man\/man.*\)/\1.gz/' -e 's/\(.*\/share\/info.*\)/\1.gz/'>> %{manifest}
find . -type l \
        | sed -e 's/^\.//' >> %{manifest}


%clean
rm -rf $RPM_BUILD_ROOT


%files -f %{manifest}
%defattr(-,root,root,-)

%docdir doc
/usr/share/doc/ViennaRNA

%changelog
* Mon Mar 26 2012 Ronny Lorenz <ronny@tbi.univie.ac.at>
- Restored z-score computation capabilities for RNALfold
* Thu Mar 08 2012 Ronny Lorenz <ronny@tbi.univie.ac.at>
- Introduced new threadsafety for several folding recursions
- Boltzmann factor scaling for RNAfold, RNAsubopt, RNAalifold, RNAplfold and RNAcofold
- Plugged several memory leaks
- Fixed fastaheader to filename bug
* Tue Jan 18 2011 Ronny Lorenz <ronny@tbi.univie.ac.at>
- created first rpm version of Vienna RNA Package 2.0
- Energy model for all secondary structure folding algorithms has changed!
- More programs that interface the RNAlib included
* Tue Jan 26 2010 Richard Neuboeck <hawk@tbi.univie.ac.at>
- install perl stuff to vendor dir instead of default
* Tue Jan 26 2010 Richard Neuboeck <hawk@tbi.univie.ac.at>
- Removed forester from install due to compile problems in F12
