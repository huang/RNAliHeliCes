/* {{{

    This file is part of gapc (GAPC - Grammars, Algebras, Products - Compiler;
      a system to compile algebraic dynamic programming programs)

    Copyright (C) 2008-2011  Georg Sauthoff
         email: gsauthof@techfak.uni-bielefeld.de or gsauthof@sdf.lonestar.org

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

}}} */


#ifndef RNA_HH
#define RNA_HH

#include "sequence.hh"
#include "subsequence.hh"

#include <cstring>

extern "C" {
#include <rnalib.h>
}

template<typename alphabet, typename T>
inline bool basepairing(const alphabet *seq,
    T i, T j)
{
  if (j<=i+1)
    return false;
  char a = seq[i];
  char b = seq[j-1];

  switch (a) {
    case A_BASE :
      switch (b) {
        case U_BASE : return true;
      }
      break;
    case U_BASE :
      switch (b) {
        case A_BASE : return true;
        case G_BASE : return true;
      }
      break;
    case G_BASE :
      switch (b) {
        case C_BASE : return true;
        case U_BASE : return true;
      }
      break;
    case C_BASE :
      switch (b) {
        case G_BASE : return true;
      }
      break;
  }
  return false;
}

template<typename alphabet, typename pos_type, typename T>
inline bool basepairing(const Basic_Sequence<alphabet, pos_type> &seq,
    T i, T j)
{
  if (j<=i+1)
    return false;
  for (unsigned k = 0; k < seq.rows(); ++k)
    if (!basepairing(seq.row(k), i, j))
      return false;
  return true;
}

template<typename alphabet, typename pos_type, typename T>
inline bool basepairing(const Basic_Sequence<alphabet, pos_type> &seq,
    T i, T j, int threshold) //Georg, why is threshold an int and not a float, since it should be a ratio between 0 and 1.0?
{
  if (j<=i+1)
    return false;
  unsigned valid = 0;
  unsigned invalid = 0;
  for (unsigned k = 0; k < seq.rows(); ++k) {
	if ((char(seq.row(k)[i]) == GAP_BASE) && (char(seq.row(k)[j-1]) == GAP_BASE)) continue; //GAP-GAP pairs doesn't count at all! Thus, the denominator is not seq.rows() but valid+invalid pairs.
    if (basepairing(seq.row(k), i, j)) {
      valid += 100;
	} else {
	  invalid += 100;
	}
  }
  assert(threshold>=0);
  return 100.0 * float(valid)/(valid+invalid) >= unsigned(threshold);
}

template<typename alphabet, typename pos_type, typename T>
inline bool stackpairing(const Basic_Sequence<alphabet, pos_type> &seq,
    T i, T j)
{
  return (i+3 < j) && basepairing(seq, i, j) && basepairing(seq, i+1, j-1);
}

template<typename alphabet, typename pos_type, typename T>
inline bool stackpairing(const Basic_Sequence<alphabet, pos_type> &seq,
    T i, T j, int threshold)
{
  return (i+3 < j) && basepairing(seq, i, j, threshold)
                   && basepairing(seq, i+1, j-1, threshold);
}

#include <exception>

#include <cstring>

class BaseException : public std::exception {
  private:
    char z;
    char *msg;
  public:
    BaseException(char c) : std::exception(), z(c), msg(0)
    {
      msg = new char[100];
      msg[0] = 0;
    }
    ~BaseException() throw() { delete[] msg; }
    const char* what() const throw()
    {
      if (!*msg) {
        std::strcpy(msg, "Unknown base '");
        unsigned l = std::strlen(msg);
        msg[l] = z;
        msg[l+1] = 0;
        std::strcat(msg, "' in input.");
      }
      return msg;
    }
};

inline char char_to_base(char a)
{
  char c = lower_case(a);
  switch (c) {
    case 'n' : return N_BASE;
    case 'a' : return A_BASE;
    case 'c' : return C_BASE;
    case 'g' : return G_BASE;
    case 'u' : return U_BASE;
    case '_' : return GAP_BASE;
    default: throw BaseException(a);
  };
  return 0;
}

inline char base_to_char(char a)
{
  switch (a) {
    case N_BASE : return 'n';
    case A_BASE : return 'a';
    case C_BASE : return 'c';
    case G_BASE : return 'g';
    case U_BASE : return 'u';
    case GAP_BASE : return '_';
    default: throw BaseException(a);
  };
  return 0;
}

inline void to_base(char &a, unsigned rows)
{
  a = char_to_base(a);
}

inline void to_base(M_Char &m, unsigned rows)
{
  for (unsigned r = 0; r < rows; ++r)
    m.column(r) = char_to_base(m.column(r));
}

template<typename pos_type>
inline void char_to_rna(Basic_Sequence<M_Char, pos_type> &seq)
{
  typedef char alphabet2;
  for (typename Basic_Sequence<M_Char, pos_type>::iterator i = seq.begin();
       i != seq.end(); ++i)
    to_base(*i, seq.rows());
  for (pos_type r = 0; r < seq.rows(); ++r) {
    alphabet2 *s = seq.row(r);
    for (pos_type i = 0; i < seq.size(); ++i, ++s)
      *s = char_to_base(*s);
  }
}

template<typename alphabet, typename pos_type>
inline void char_to_rna(Basic_Sequence<alphabet, pos_type> &seq)
{
  typedef char alphabet2;
  for (typename Basic_Sequence<alphabet, pos_type>::iterator i = seq.begin();
       i != seq.end(); ++i)
    to_base(*i, seq.rows());
  if (seq.rows() == 1)
    return;
  for (pos_type r = 0; r < seq.rows(); ++r) {
    alphabet2 *s = seq.row(r);
    for (pos_type i = 0; i < seq.size(); ++i, ++s)
      *s = char_to_base(*s);
  }
}

#include <cmath>

using std::exp;

template<typename X, typename alphabet, typename pos_type>
inline void append_deep_rna(rope::Ref<X> &str, const Basic_Subsequence<alphabet, pos_type> &sub)
{
  for (typename Basic_Subsequence<alphabet, pos_type>::const_iterator i = sub.begin();
      i != sub.end(); ++i)
    str.append(base_to_char(*i));
}

// ======== energy wrapper function ========

/*
   returns the destabilizing energy for a stem, ending with an AU, UA, GU or UG basepair. All other basepairs result in 0 energy.
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) whose left position is the 5' side of the stem
     b) a Bellman's GAP terminal (e.g. BASE or REGION) whose right position is the 3' side of the stem
   This function should be applied to all locations where a stem (i.e. stack of two or more successive basepairs) is opened and closed. Exceptions are the inner parts of hairpins, bulges and internal loops, because the AU penalty is considered in their special energy functions.
*/
template<typename alphabet, typename pos_type>
inline int termau_energy(const Basic_Subsequence<alphabet, pos_type> &a,
    const Basic_Subsequence<alphabet, pos_type> &b)
{
  int energy = 0;
  assert(a.seq->rows() == b.seq->rows());

  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += termau_energy(a.seq->row(k), a.i, b.j-1);

  return energy;
}

/*
   returns the energy value for a basepair closing an unpaired hairpin loop
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing the unpaired loop region of the hairpin
   The positions of the bases of the closing basepair are assumed to be directly left of the 5'-start of the unpaired loop region and directly right to the 3'-end of the unpaired loop region
*/
template<typename alphabet, typename pos_type>
inline int hl_energy(const Basic_Subsequence<alphabet, pos_type> &a)
{
  int energy = 0;

  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += hl_energy(a.seq->row(k), a.i-1, a.j);

  return energy;
}

/*
   similar to hl_energy, but without the stabilizing contribution of stacking the outmost bases onto the closing basepairs for hairpins with unpaired loops larger than 4
*/
template<typename alphabet, typename pos_type>
inline int hl_energy_stem(const Basic_Subsequence<alphabet, pos_type> &a)
{
  int energy = 0;
  
  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += hl_energy_stem(a.seq->row(k), a.i-1, a.j);

  return energy;
}

/*
   returns the energy value for a basepair closing an internal loop with some bases bulged at 5' and 3' side and an arbitrary closed substructure
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing the 5' unpaired loop region of the internal loop
     b) a Bellman's GAP terminal (e.g. BASE or REGION) describing the 3' unpaired loop region of the internal loop
   The positions of the bases of the closing basepair are assumed to be directly left of the 5'-start of the 5' unpaired loop region and directly right to the 3'-end of the 3' unpaired loop region
   The positions of the bases of the embedded basepair are assumed to be directly right of the 5'-end of the 5' unpaired loop region and directly left to the 5'-start of the 3' unpaired loop region
*/
template<typename alphabet, typename pos_type>
inline int il_energy(const Basic_Subsequence<alphabet, pos_type> &a,
    const Basic_Subsequence<alphabet, pos_type> &b)
{
  int energy = 0;
  assert(a.seq->rows() == b.seq->rows());

  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += il_energy(a.seq->row(k), a.i-1, a.j, b.i-1, b.j);

  return energy;
}

/*
   returns the energy value for a basepair closing an left bulge loop with some bases bulged at 5' side and an arbitrary closed substructure
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing the 5' unpaired loop region of the left bulge
     b) a Bellman's GAP terminal (e.g. BASE or REGION) describing the 3' base of the closing basepair
   The 5' position of the base of the closing basepair is assumed to be directly left of the 5'-start of the unpaired loop region
   The positions of the bases of the embedded basepair are assumed to be directly right of the 3'-end of the unpaired loop region and directly left to the 3' base of the closing basepair
*/
template<typename alphabet, typename pos_type>
inline int bl_energy(const Basic_Subsequence<alphabet, pos_type> &lr,
    const Basic_Subsequence<alphabet, pos_type> &rb)
{
  int energy = 0;
  assert(lr.seq->rows() == rb.seq->rows());

  for (unsigned k = 0; k < lr.seq->rows(); k++)
    energy += bl_energy(lr.seq->row(k), lr.i-1, lr.i, lr.j-1, rb.j-1, rb.j-2);

  return energy;
}

/*
   returns the energy value for a basepair closing an right bulge loop with some bases bulged at 3' side and an arbitrary closed substructure
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing the 5' base of the closing basepair
     b) a Bellman's GAP terminal (e.g. BASE or REGION) describing the 6' unpaired loop region of the right bulge
   The 3' position of the base of the closing basepair is assumed to be directly right of the 3'-end of the unpaired loop region
   The positions of the bases of the embedded basepair are assumed to be directly right of the 5' partner of the closing basepair and directly left to the 5'-start of the unpaired loop region
*/
template<typename alphabet, typename pos_type>
inline int br_energy(const Basic_Subsequence<alphabet, pos_type> &lb,
    const Basic_Subsequence<alphabet, pos_type> &rr)
{
  int energy = 0;
  assert(lb.seq->rows() == rr.seq->rows());

  for (unsigned k = 0; k < lb.seq->rows(); k++)
    energy += br_energy(lb.seq->row(k), lb.i, rr.i, rr.j-1, rr.j, lb.i+1);

  return energy;
}

/*
   returns the energy value for two successive basepairs which form a stack
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing the 5' base of outer basepair
     b) a Bellman's GAP terminal (e.g. BASE or REGION) describing the 3' base of outer basepair
   The positions of the bases of the embedded basepair are assumed to be directly right of the 5' partner of the closing basepair and directly left to the 3' partner of the closing basepair
*/
template<typename alphabet, typename pos_type>
inline int sr_energy(const Basic_Subsequence<alphabet, pos_type> &a,
    const Basic_Subsequence<alphabet, pos_type> &b)
{
  int energy = 0;
  assert(a.seq->rows() == b.seq->rows());

  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += sr_energy(a.seq->row(k), a.i, b.j-1);

  return energy;
}

/*
   same as sr_energy but independent of the input RNA sequence. Input are just char for RNA-bases. This function is necessary to compute the coaxial stacking of the two crossing stems of a csr (canonical simple recursive) pseudoknot or csr kissing hairpin
*/
template<typename alphabet, typename pos_type>
inline int sr_pk_energy(char a, char b, char c, char d)
{
  return sr_pk_energy(a,b,c,d);
}

/*
   returns the energy value for a base directly left of a stem, which dangles onto this stem from outside
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing the outermost 5' base of stem
     b) a Bellman's GAP terminal (e.g. BASE or REGION) describing the outermost 3' base of stem
   The position of the dangling base is assumed to be directly left of the outermost 5' partner of the stems basepair
*/
template<typename alphabet, typename pos_type>
inline int dl_energy(const Basic_Subsequence<alphabet, pos_type> &a,
    const Basic_Subsequence<alphabet, pos_type> &b)
{
  int energy = 0;
  assert(a.seq->rows() == b.seq->rows());

  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += dl_energy(a.seq->row(k), a.i, b.j-1);

  return energy;
}

/*
   returns the energy value for a base directly right of a stem, which dangles onto this stem from outside
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing the outermost 5' base of stem
     b) a Bellman's GAP terminal (e.g. BASE or REGION) describing the outermost 3' base of stem
   The position of the dangling base is assumed to be directly right to the outermost 3' partner of the stems basepair
*/
template<typename alphabet, typename pos_type>
inline int dr_energy(const Basic_Subsequence<alphabet, pos_type> &a,
    const Basic_Subsequence<alphabet, pos_type> &b)
{
  int energy = 0;
  assert(a.seq->rows() == b.seq->rows());

  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += dr_energy(a.seq->row(k), a.i, b.j-1, a.seq->n);

  return energy;
}

/*
   returns the energy value for a base directly 3' of a stem, which dangles onto this stem from inside
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing the innermost 5' base of stem
     b) a Bellman's GAP terminal (e.g. BASE or REGION) describing the innermost 3' base of stem
   The position of the dangling base is assumed to be directly right of the 3' partner of the innermost basepair of the stem
*/
template<typename alphabet, typename pos_type>
inline int dli_energy(const Basic_Subsequence<alphabet, pos_type> &a,
    const Basic_Subsequence<alphabet, pos_type> &b)
{
  int energy = 0;
  assert(a.seq->rows() == b.seq->rows());

  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += dli_energy(a.seq->row(k), a.i, b.j-1);

  return energy;
}

/*
   returns the energy value for a base directly 5' of a stem, which dangles onto this stem from inside
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing the innermost 5' base of stem
     b) a Bellman's GAP terminal (e.g. BASE or REGION) describing the innermost 3' base of stem
   The position of the dangling base is assumed to be directly left of the 5' partner of the innermost basepair of the stem
*/
template<typename alphabet, typename pos_type>
inline int dri_energy(const Basic_Subsequence<alphabet, pos_type> &a,
    const Basic_Subsequence<alphabet, pos_type> &b)
{
  int energy = 0;
  assert(a.seq->rows() == b.seq->rows());

  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += dri_energy(a.seq->row(k), a.i, b.j-1);

  return energy;
}

/*
   returns the energy value for two bases directly surrounding a stem, which dangles onto this stem from outside
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing the outermost 5' base of stem
     b) a Bellman's GAP terminal (e.g. BASE or REGION) describing the outermost 3' base of stem
   The positions of the dangling bases are assumed to be directly left of the 5' partner and right of the 3' partner of the outermost basepair of the stem
*/
template<typename alphabet, typename pos_type>
inline int ext_mismatch_energy(const Basic_Subsequence<alphabet, pos_type> &a,
    const Basic_Subsequence<alphabet, pos_type> &b)
{
  int energy = 0;
  assert(a.seq->rows() == b.seq->rows());

  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += ext_mismatch_energy(a.seq->row(k), a.i, b.j-1, a.seq->n);

  return energy;
}

/*
   returns the energy value for a base directly 3' of a stem and a second base directly 5' of the same stem, which both dangle onto this stem from inside
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing the innermost 5' base of stem
     b) a Bellman's GAP terminal (e.g. BASE or REGION) describing the innermost 3' base of stem
   The positions of the dangling bases are assumed to be directly right of the 5' partner and left of the 3' partner of the innermost basepair of the stem
*/
template<typename alphabet, typename pos_type>
inline int ml_mismatch_energy(const Basic_Subsequence<alphabet, pos_type> &a,
    const Basic_Subsequence<alphabet, pos_type> &b)
{
  int energy = 0;
  assert(a.seq->rows() == b.seq->rows());

  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += ml_mismatch_energy(a.seq->row(k), a.i, b.j-1);

  return energy;
}

/*
   returns the energy value for initializing an arbitrary closed substructure within a multiloop
*/
int ul_energy();

/*
   returns the energy value for initializing a multiloop
*/
int ml_energy();

/*
   returns the energy value for an unpaired base outside of closed substructures, i.e. left or right of closed substructures, between two substructures or within multiloops but not in multiloop stems
*/
int sbase_energy();

/*
   returns the energy value for a stretch of unpaired bases outside of closed substructures, i.e. left or right of closed substructures, between two substructures or within multiloops but not in multiloop stems
   Input is
     a) a Bellman's GAP terminal (e.g. BASE or REGION) describing region of unpaired bases
*/
template<typename alphabet, typename pos_type>
inline int ss_energy(const Basic_Subsequence<alphabet, pos_type> &a)
{
  int energy = 0;

  for (unsigned k = 0; k < a.seq->rows(); k++)
    energy += ss_energy(a.i, a.j);

  return energy;
}

/*
   a special version of dl_dangle, which is independent of the given input RNA sequence. This is necessary for MacroState partition function calculation, when the answer is a tuple rather than a single value to account simultaneously for different dangling cases.
   Input is
     a) the bit encoded dangling base
     b) the bit encoded 5' partner of the basepair terminating the stem
     c) the bit encoded 3' partner of the basepair terminating the stem
*/
template<typename alphabet, typename pos_type>
inline int dl_dangle_dg(enum base_t dangle, enum base_t i, enum base_t j)
{
  return dl_dangle_dg(dangle, i, j);
}

/*
   a special version of dr_dangle, which is independent of the given input RNA sequence. This is necessary for MacroState partition function calculation, when the answer is a tuple rather than a single value to account simultaneously for different dangling cases.
   Input is
     a) the bit encoded 5' partner of the basepair terminating the stem
     b) the bit encoded 3' partner of the basepair terminating the stem
     c) the bit encoded dangling base
*/
template<typename alphabet, typename pos_type>
inline int dr_dangle_dg(enum base_t i, enum base_t j, enum base_t dangle)
{
  return dr_dangle_dg(i, j, dangle);
}

#include "table.hh"

template<typename alphabet = char, typename pos_type = unsigned int>
class iupac_filter {
  private:
    struct matrix_t {
      std::vector<bool> v;
      Table::DiagIndex<pos_type> index;
      pos_type n;
      bool get(pos_type i, pos_type j) const { return v[index(i, j, n)]; }
      void set(pos_type i, pos_type j, bool b) { v[index(i, j, n)] = b; }
      void init(pos_type l) { n = l; v.resize(index(l)); }
    };
    matrix_t array;

    bool match(char base,  char iupac) const
    {
      assert(base>=0);
      assert(base<5);
      assert(iupac>=0);
      assert(iupac<12);
      return iupac_match(base, iupac);
    }
    void convert_iupac(std::vector<char> &v) const
    {
      for (pos_type i=0; i<v.size(); ++i) {
        char c = lower_case(v[i]);
        switch (c) {
          case 'n' : v[i] = 0; break;
          case 'a' : v[i] = 1; break;
          case 'c' : v[i] = 2; break;
          case 'g' : v[i] = 3; break;
          case 'u' : v[i] = 4; break;
          case '_' : v[i] = 5; break;
          case 'b' : v[i] = 6; break;
          case 'd' : v[i] = 7; break;
          case 'h' : v[i] = 8; break;
          case 'r' : v[i] = 9; break;
          case 'v' : v[i] = 10; break;
          case 'y' : v[i] = 11; break;
          default: throw BaseException(v[i]);
        };
      }
    }
    void mark(pos_type i, pos_type j)
    {
      if (array.get(i, j))
        return;
      for (pos_type x = i; x>0; --x) {
        if (array.get(x, j))
          break;
        for (pos_type y = j; y<=array.n; ++y) {
          if (array.get(x, y))
            break;
          array.set(x, y, true);
        }
      }
      pos_type x = 0;
      for (pos_type y = j; y<=array.n; ++y) {
        if (array.get(x, y))
          break;
        array.set(x, y, true);
      }
    }
  public:
    void init(const Basic_Sequence<char, pos_type> &seq, const char *pat)
    {
      array.init(seq.size());

      pos_type m = std::strlen(pat);
      std::vector<char> pattern(pat, pat+m);
      convert_iupac(pattern);
      std::vector<bool> v(m), w(m);
      for (pos_type j = 0; j<seq.size(); ++j) {
        if (match(seq[j], pattern[0]))
          v[0] = true;
        for (pos_type i = 1; i<m; ++i) {
          v[i] = w[i-1] && match(seq[j], pattern[i]);
        }
        if (v[m-1])
          mark(j+1-m, j+1);
        std::swap(v, w);
      }
    }
    bool query(pos_type a, pos_type b)
    {
      assert(a<=b);
      return array.get(a, b);
    }
};


#endif
