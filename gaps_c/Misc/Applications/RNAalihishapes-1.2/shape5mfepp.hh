
// A dynamic programming evaluator generated by GAP-C.
// 
//   GAP-C version:
//     bellmansgapc-2020.01.08
// 
//   GAP-C call:
//     gapc -I ../../../ -i shape5mfepp ../../../ali_microstate.gap -o shape5mfepp.cc 
// 
// 


#ifndef shape5mfepp_hh
#define shape5mfepp_hh

#include "rtlib/adp.hh"

typedef Basic_Subsequence<M_Char, unsigned> TUSubsequence;

typedef Shape shape_t;
#include <rtlib/subopt.hh>
#include "rna.hh"
#include "Extensions/alifold.hh"
#include "Extensions/mfesubopt.hh"
#include "Extensions/probabilities.hh"
#include "Extensions/typesRNAfolding.hh"
#include "Extensions/shapes.hh"

#include <rtlib/generic_opts.hh>
#include "rtlib/pareto_dom_sort.hh"
#include "rtlib/pareto_yukish_ref.hh"

class shape5mfepp {

  public:
Basic_Sequence<M_Char> t_0_seq;
unsigned int t_0_left_most;
unsigned int t_0_right_most;

List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > LBBshape_firstG_mfecovar_secondG_E_firstG_string_secondG_EM_zero;
std::pair<std::pair<Shape, mfecovar> , String>  BBshape_firstG_mfecovar_secondG_E_firstG_string_secondG_E_zero;

class dangle_table_t {

private:

unsigned int t_0_left_most;
unsigned int t_0_right_most;
std::vector<List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > > array;
std::vector<bool> tabulated;
unsigned int t_0_n;
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > zero;
unsigned int size()
{
  return (1 * ((((t_0_n * (t_0_n + 1)) / 2) + t_0_n) + 1));
}


public:

dangle_table_t()
{
  empty(zero);
}

void init(unsigned int t_0_n_, const std::string &tname)
{
t_0_n = t_0_n_;
t_0_left_most = 0;
t_0_right_most = t_0_n;
unsigned int newsize = size();
array.resize(newsize);
tabulated.clear();
tabulated.resize(newsize);
}
bool is_tabulated(unsigned int t_0_i, unsigned int t_0_j)
{
  if (((t_0_j - t_0_i) < 5))
    {
      return true;
    }

  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  return tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void clear() { tabulated.clear(); }
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  get(unsigned int t_0_i, unsigned int t_0_j)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 5))
    {
      return zero;
    }

  assert( tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))]);
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  return array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void set(unsigned int t_0_i, unsigned int t_0_j, List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > e)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 5))
    {
      assert( 0);
    }

  assert( !is_tabulated(t_0_i, t_0_j));
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = e;
  tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = true;
}


};
dangle_table_t dangle_table;


class iloop_table_t {

private:

unsigned int t_0_left_most;
unsigned int t_0_right_most;
std::vector<List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > > array;
std::vector<bool> tabulated;
unsigned int t_0_n;
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > zero;
unsigned int size()
{
  return (1 * ((((t_0_n * (t_0_n + 1)) / 2) + t_0_n) + 1));
}


public:

iloop_table_t()
{
  empty(zero);
}

void init(unsigned int t_0_n_, const std::string &tname)
{
t_0_n = t_0_n_;
t_0_left_most = 0;
t_0_right_most = t_0_n;
unsigned int newsize = size();
array.resize(newsize);
tabulated.clear();
tabulated.resize(newsize);
}
bool is_tabulated(unsigned int t_0_i, unsigned int t_0_j)
{
  if (((t_0_j - t_0_i) < 9))
    {
      return true;
    }

  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  return tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void clear() { tabulated.clear(); }
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  get(unsigned int t_0_i, unsigned int t_0_j)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 9))
    {
      return zero;
    }

  assert( tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))]);
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  return array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void set(unsigned int t_0_i, unsigned int t_0_j, List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > e)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 9))
    {
      assert( 0);
    }

  assert( !is_tabulated(t_0_i, t_0_j));
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = e;
  tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = true;
}


};
iloop_table_t iloop_table;


class ml_comps_table_t {

private:

unsigned int t_0_left_most;
unsigned int t_0_right_most;
std::vector<List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > > array;
std::vector<bool> tabulated;
unsigned int t_0_n;
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > zero;
unsigned int size()
{
  return (1 * ((((t_0_n * (t_0_n + 1)) / 2) + t_0_n) + 1));
}


public:

ml_comps_table_t()
{
  empty(zero);
}

void init(unsigned int t_0_n_, const std::string &tname)
{
t_0_n = t_0_n_;
t_0_left_most = 0;
t_0_right_most = t_0_n;
unsigned int newsize = size();
array.resize(newsize);
tabulated.clear();
tabulated.resize(newsize);
}
bool is_tabulated(unsigned int t_0_i, unsigned int t_0_j)
{
  if (((t_0_j - t_0_i) < 10))
    {
      return true;
    }

  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  return tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void clear() { tabulated.clear(); }
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  get(unsigned int t_0_i, unsigned int t_0_j)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 10))
    {
      return zero;
    }

  assert( tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))]);
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  return array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void set(unsigned int t_0_i, unsigned int t_0_j, List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > e)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 10))
    {
      assert( 0);
    }

  assert( !is_tabulated(t_0_i, t_0_j));
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = e;
  tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = true;
}


};
ml_comps_table_t ml_comps_table;


class ml_comps1_table_t {

private:

unsigned int t_0_left_most;
unsigned int t_0_right_most;
std::vector<List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > > array;
std::vector<bool> tabulated;
unsigned int t_0_n;
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > zero;
unsigned int size()
{
  return (1 * ((((t_0_n * (t_0_n + 1)) / 2) + t_0_n) + 1));
}


public:

ml_comps1_table_t()
{
  empty(zero);
}

void init(unsigned int t_0_n_, const std::string &tname)
{
t_0_n = t_0_n_;
t_0_left_most = 0;
t_0_right_most = t_0_n;
unsigned int newsize = size();
array.resize(newsize);
tabulated.clear();
tabulated.resize(newsize);
}
bool is_tabulated(unsigned int t_0_i, unsigned int t_0_j)
{
  if (((t_0_j - t_0_i) < 5))
    {
      return true;
    }

  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  return tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void clear() { tabulated.clear(); }
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  get(unsigned int t_0_i, unsigned int t_0_j)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 5))
    {
      return zero;
    }

  assert( tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))]);
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  return array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void set(unsigned int t_0_i, unsigned int t_0_j, List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > e)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 5))
    {
      assert( 0);
    }

  assert( !is_tabulated(t_0_i, t_0_j));
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = e;
  tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = true;
}


};
ml_comps1_table_t ml_comps1_table;


class strong_table_t {

private:

unsigned int t_0_left_most;
unsigned int t_0_right_most;
std::vector<List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > > array;
std::vector<bool> tabulated;
unsigned int t_0_n;
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > zero;
unsigned int size()
{
  return (1 * ((((t_0_n * (t_0_n + 1)) / 2) + t_0_n) + 1));
}


public:

strong_table_t()
{
  empty(zero);
}

void init(unsigned int t_0_n_, const std::string &tname)
{
t_0_n = t_0_n_;
t_0_left_most = 0;
t_0_right_most = t_0_n;
unsigned int newsize = size();
array.resize(newsize);
tabulated.clear();
tabulated.resize(newsize);
}
bool is_tabulated(unsigned int t_0_i, unsigned int t_0_j)
{
  if (((t_0_j - t_0_i) < 5))
    {
      return true;
    }

  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  return tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void clear() { tabulated.clear(); }
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  get(unsigned int t_0_i, unsigned int t_0_j)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 5))
    {
      return zero;
    }

  assert( tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))]);
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  return array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void set(unsigned int t_0_i, unsigned int t_0_j, List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > e)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 5))
    {
      assert( 0);
    }

  assert( !is_tabulated(t_0_i, t_0_j));
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = e;
  tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = true;
}


};
strong_table_t strong_table;


class struct_table_t {

private:

unsigned int t_0_left_most;
unsigned int t_0_right_most;
std::vector<List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > > array;
std::vector<bool> tabulated;
unsigned int t_0_n;
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > zero;
unsigned int size()
{
  return (1 * ((t_0_n + 1) * 1));
}


public:

struct_table_t()
{
  empty(zero);
}

void init(unsigned int t_0_n_, const std::string &tname)
{
t_0_n = t_0_n_;
t_0_left_most = 0;
t_0_right_most = t_0_n;
unsigned int newsize = size();
array.resize(newsize);
tabulated.clear();
tabulated.resize(newsize);
}
bool is_tabulated(unsigned int t_0_i)
{
  unsigned int t_0_j = t_0_n;
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if ((t_0_j < (t_0_n - 0)))
    {
      return true;
    }

  unsigned int t_0_real_j = (t_0_n - t_0_j);
  return tabulated[(0 + (1 * (t_0_i + (t_0_real_j * (t_0_n + 1)))))];
}


void clear() { tabulated.clear(); }
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  get(unsigned int t_0_i)
{
  unsigned int t_0_j = t_0_n;
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if ((t_0_j < (t_0_n - 0)))
    {
      return zero;
    }

  unsigned int t_0_real_j = (t_0_n - t_0_j);
  assert( tabulated[(0 + (1 * (t_0_i + (t_0_real_j * (t_0_n + 1)))))]);
  assert( ((0 + (1 * (t_0_i + (t_0_real_j * (t_0_n + 1))))) < size()));
  return array[(0 + (1 * (t_0_i + (t_0_real_j * (t_0_n + 1)))))];
}


void set(unsigned int t_0_i, List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > e)
{
  unsigned int t_0_j = t_0_n;
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if ((t_0_j < (t_0_n - 0)))
    {
      return;
    }

  unsigned int t_0_real_j = (t_0_n - t_0_j);
  assert( !is_tabulated(t_0_i));
  assert( ((0 + (1 * (t_0_i + (t_0_real_j * (t_0_n + 1))))) < size()));
  array[(0 + (1 * (t_0_i + (t_0_real_j * (t_0_n + 1)))))] = e;
  tabulated[(0 + (1 * (t_0_i + (t_0_real_j * (t_0_n + 1)))))] = true;
}


};
struct_table_t struct_table;


class weak_table_t {

private:

unsigned int t_0_left_most;
unsigned int t_0_right_most;
std::vector<List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > > array;
std::vector<bool> tabulated;
unsigned int t_0_n;
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > zero;
unsigned int size()
{
  return (1 * ((((t_0_n * (t_0_n + 1)) / 2) + t_0_n) + 1));
}


public:

weak_table_t()
{
  empty(zero);
}

void init(unsigned int t_0_n_, const std::string &tname)
{
t_0_n = t_0_n_;
t_0_left_most = 0;
t_0_right_most = t_0_n;
unsigned int newsize = size();
array.resize(newsize);
tabulated.clear();
tabulated.resize(newsize);
}
bool is_tabulated(unsigned int t_0_i, unsigned int t_0_j)
{
  if (((t_0_j - t_0_i) < 5))
    {
      return true;
    }

  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  return tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void clear() { tabulated.clear(); }
List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  get(unsigned int t_0_i, unsigned int t_0_j)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 5))
    {
      return zero;
    }

  assert( tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))]);
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  return array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))];
}


void set(unsigned int t_0_i, unsigned int t_0_j, List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > e)
{
  assert( (t_0_i <= t_0_j));
  assert( (t_0_j <= t_0_n));
  if (((t_0_j - t_0_i) < 5))
    {
      assert( 0);
    }

  assert( !is_tabulated(t_0_i, t_0_j));
  assert( ((0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i))) < size()));
  array[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = e;
  tabulated[(0 + (1 * (((t_0_j * (t_0_j + 1)) / 2) + t_0_i)))] = true;
}


};
weak_table_t weak_table;



void init(const gapc::Opts &opts)
{
const std::vector<std::pair<const char *, unsigned> > &inp = opts.inputs;
if(inp.size() != 1)
  throw gapc::OptException("Number of input sequences does not match.");

  t_0_seq.copy(inp[0].first, inp[0].second);
char_to_rna(t_0_seq);
  dangle_table.init( t_0_seq.size(), "dangle_table");
  iloop_table.init( t_0_seq.size(), "iloop_table");
  ml_comps_table.init( t_0_seq.size(), "ml_comps_table");
  ml_comps1_table.init( t_0_seq.size(), "ml_comps1_table");
  strong_table.init( t_0_seq.size(), "strong_table");
  struct_table.init( t_0_seq.size(), "struct_table");
  weak_table.init( t_0_seq.size(), "weak_table");
empty(LBBshape_firstG_mfecovar_secondG_E_firstG_string_secondG_EM_zero);
empty(BBshape_firstG_mfecovar_secondG_E_firstG_string_secondG_E_zero);

t_0_left_most = 0;
t_0_right_most = t_0_seq.size();
}

  private:
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  nt_dangle(unsigned int t_0_i, unsigned int t_0_j);
    std::pair<std::pair<Shape, mfecovar> , String>  nt_hairpin(unsigned int t_0_i, unsigned int t_0_j);
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  nt_iloop(unsigned int t_0_i, unsigned int t_0_j);
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > nt_leftB(unsigned int t_0_i, unsigned int t_0_j);
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  nt_ml_comps(unsigned int t_0_i, unsigned int t_0_j);
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  nt_ml_comps1(unsigned int t_0_i, unsigned int t_0_j);
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > nt_multiloop(unsigned int t_0_i, unsigned int t_0_j);
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > nt_rightB(unsigned int t_0_i, unsigned int t_0_j);
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > nt_stack(unsigned int t_0_i, unsigned int t_0_j);
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  nt_strong(unsigned int t_0_i, unsigned int t_0_j);
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  nt_struct(unsigned int t_0_i);
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  nt_weak(unsigned int t_0_i, unsigned int t_0_j);

    std::pair<std::pair<shape_t, mfecovar> , String>  addss(const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_rb);
    std::pair<std::pair<shape_t, mfecovar> , String>  bl(const TUSubsequence & p_p_lb, const TUSubsequence & p_p_lregion, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_rb);
    std::pair<std::pair<shape_t, mfecovar> , String>  br(const TUSubsequence & p_p_lb, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_rregion, const TUSubsequence & p_p_rb);
    std::pair<std::pair<shape_t, mfecovar> , String>  cadd(const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_le, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_re);
    std::pair<std::pair<shape_t, mfecovar> , String>  drem(const TUSubsequence & p_p_lloc, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_rloc);
    std::pair<std::pair<shape_t, mfecovar> , String>  edl(const TUSubsequence & p_p_lb, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_rloc);
    std::pair<std::pair<shape_t, mfecovar> , String>  edlr(const TUSubsequence & p_p_lb, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_rb);
    std::pair<std::pair<shape_t, mfecovar> , String>  edr(const TUSubsequence & p_p_lloc, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_rb);
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > h(List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > i);
template <typename Iterator>
    List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > h(std::pair<Iterator, Iterator> i)
;
    std::pair<std::pair<shape_t, mfecovar> , String>  hl(const TUSubsequence & p_p_lb, const TUSubsequence & p_p_region, const TUSubsequence & p_p_rb);
    std::pair<std::pair<shape_t, mfecovar> , String>  il(const TUSubsequence & p_p_lb, const TUSubsequence & p_p_lregion, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_rregion, const TUSubsequence & p_p_rb);
    std::pair<std::pair<shape_t, mfecovar> , String>  incl(const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e);
    std::pair<std::pair<shape_t, mfecovar> , String>  ml(const TUSubsequence & p_p_lb, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_rb);
    std::pair<std::pair<shape_t, mfecovar> , String>  mldl(const TUSubsequence & p_p_lb, const TUSubsequence & p_p_dl, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_rb);
    std::pair<std::pair<shape_t, mfecovar> , String>  mldlr(const TUSubsequence & p_p_lb, const TUSubsequence & p_p_dl, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_dr, const TUSubsequence & p_p_rb);
    std::pair<std::pair<shape_t, mfecovar> , String>  mldr(const TUSubsequence & p_p_lb, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_dr, const TUSubsequence & p_p_rb);
    std::pair<std::pair<shape_t, mfecovar> , String>  nil(const TUSubsequence & p_p_loc);
    std::pair<std::pair<shape_t, mfecovar> , String>  sadd(const TUSubsequence & p_p_b, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e);
    std::pair<std::pair<shape_t, mfecovar> , String>  sr(const TUSubsequence & p_p_lb, const std::pair<std::pair<shape_t, mfecovar> , String> & p_p_e, const TUSubsequence & p_p_rb);


    std::pair<shape_t, mfecovar>  addss_l(const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_rb);
    std::pair<shape_t, mfecovar>  bl_l(const TUSubsequence & p_lb, const TUSubsequence & p_lregion, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_rb);
    std::pair<shape_t, mfecovar>  br_l(const TUSubsequence & p_lb, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_rregion, const TUSubsequence & p_rb);
    std::pair<shape_t, mfecovar>  cadd_l(const std::pair<shape_t, mfecovar> & p_le, const std::pair<shape_t, mfecovar> & p_re);
    std::pair<shape_t, mfecovar>  drem_l(const TUSubsequence & p_lloc, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_rloc);
    std::pair<shape_t, mfecovar>  edl_l(const TUSubsequence & p_lb, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_rloc);
    std::pair<shape_t, mfecovar>  edlr_l(const TUSubsequence & p_lb, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_rb);
    std::pair<shape_t, mfecovar>  edr_l(const TUSubsequence & p_lloc, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_rb);
    List_Ref<std::pair<Shape, mfecovar> > h_l(List_Ref<std::pair<Shape, mfecovar> > i);
template <typename Iterator>
    List_Ref<std::pair<Shape, mfecovar> > h_l(std::pair<Iterator, Iterator> i)
;
    std::pair<shape_t, mfecovar>  hl_l(const TUSubsequence & p_lb, const TUSubsequence & p_region, const TUSubsequence & p_rb);
    std::pair<shape_t, mfecovar>  il_l(const TUSubsequence & p_lb, const TUSubsequence & p_lregion, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_rregion, const TUSubsequence & p_rb);
    std::pair<shape_t, mfecovar>  incl_l(const std::pair<shape_t, mfecovar> & p_e);
    std::pair<shape_t, mfecovar>  ml_l(const TUSubsequence & p_lb, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_rb);
    std::pair<shape_t, mfecovar>  mldl_l(const TUSubsequence & p_lb, const TUSubsequence & p_dl, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_rb);
    std::pair<shape_t, mfecovar>  mldlr_l(const TUSubsequence & p_lb, const TUSubsequence & p_dl, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_dr, const TUSubsequence & p_rb);
    std::pair<shape_t, mfecovar>  mldr_l(const TUSubsequence & p_lb, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_dr, const TUSubsequence & p_rb);
    std::pair<shape_t, mfecovar>  nil_l(const TUSubsequence & p_loc);
    std::pair<shape_t, mfecovar>  sadd_l(const TUSubsequence & p_b, const std::pair<shape_t, mfecovar> & p_e);
    std::pair<shape_t, mfecovar>  sr_l(const TUSubsequence & p_lb, const std::pair<shape_t, mfecovar> & p_e, const TUSubsequence & p_rb);


    shape_t addss_l_l(shape_t e, const TUSubsequence & rb);
    shape_t bl_l_l(const TUSubsequence & lb, const TUSubsequence & lregion, shape_t e, const TUSubsequence & rb);
    shape_t br_l_l(const TUSubsequence & lb, shape_t e, const TUSubsequence & rregion, const TUSubsequence & rb);
    shape_t cadd_l_l(shape_t le, shape_t re);
    shape_t drem_l_l(const TUSubsequence & lloc, shape_t e, const TUSubsequence & rloc);
    shape_t edl_l_l(const TUSubsequence & lb, shape_t e, const TUSubsequence & rloc);
    shape_t edlr_l_l(const TUSubsequence & lb, shape_t e, const TUSubsequence & rb);
    shape_t edr_l_l(const TUSubsequence & lloc, shape_t e, const TUSubsequence & rb);
    List_Ref<shape_t> h_l_l(List_Ref<shape_t> i);
template <typename Iterator>
    List_Ref<shape_t> h_l_l(std::pair<Iterator, Iterator> i)
;
    shape_t hl_l_l(const TUSubsequence & lb, const TUSubsequence & region, const TUSubsequence & rb);
    shape_t il_l_l(const TUSubsequence & lb, const TUSubsequence & lregion, shape_t e, const TUSubsequence & rregion, const TUSubsequence & rb);
    shape_t incl_l_l(shape_t e);
    shape_t ml_l_l(const TUSubsequence & lb, shape_t e, const TUSubsequence & rb);
    shape_t mldl_l_l(const TUSubsequence & lb, const TUSubsequence & dl, shape_t e, const TUSubsequence & rb);
    shape_t mldlr_l_l(const TUSubsequence & lb, const TUSubsequence & dl, shape_t e, const TUSubsequence & dr, const TUSubsequence & rb);
    shape_t mldr_l_l(const TUSubsequence & lb, shape_t e, const TUSubsequence & dr, const TUSubsequence & rb);
    shape_t nil_l_l(const TUSubsequence & loc);
    shape_t sadd_l_l(const TUSubsequence & b, shape_t e);
    shape_t sr_l_l(const TUSubsequence & lb, shape_t e, const TUSubsequence & rb);


    mfecovar addss_l_r(const mfecovar & x, const TUSubsequence & r);
    mfecovar bl_l_r(const TUSubsequence & lb, const TUSubsequence & lr, const mfecovar & x, const TUSubsequence & rb);
    mfecovar br_l_r(const TUSubsequence & lb, const mfecovar & x, const TUSubsequence & rr, const TUSubsequence & rb);
    mfecovar cadd_l_r(const mfecovar & x, const mfecovar & y);
    mfecovar drem_l_r(const TUSubsequence & lb, const mfecovar & x, const TUSubsequence & rb);
    mfecovar edl_l_r(const TUSubsequence & ldangle, const mfecovar & x, const TUSubsequence & rb);
    mfecovar edlr_l_r(const TUSubsequence & ldangle, const mfecovar & x, const TUSubsequence & rdangle);
    mfecovar edr_l_r(const TUSubsequence & lb, const mfecovar & x, const TUSubsequence & rdangle);
    mfecovar h_l_r(List_Ref<mfecovar> i);
template <typename Iterator>
    mfecovar h_l_r(std::pair<Iterator, Iterator> i)
;
    mfecovar hl_l_r(const TUSubsequence & lb, const TUSubsequence & r, const TUSubsequence & rb);
    mfecovar il_l_r(const TUSubsequence & lb, const TUSubsequence & lr, const mfecovar & x, const TUSubsequence & rr, const TUSubsequence & rb);
    mfecovar incl_l_r(const mfecovar & x);
    mfecovar ml_l_r(const TUSubsequence & lb, const mfecovar & x, const TUSubsequence & rb);
    mfecovar mldl_l_r(const TUSubsequence & lb, const TUSubsequence & dl, const mfecovar & x, const TUSubsequence & rb);
    mfecovar mldlr_l_r(const TUSubsequence & lb, const TUSubsequence & dl, const mfecovar & x, const TUSubsequence & dr, const TUSubsequence & rb);
    mfecovar mldr_l_r(const TUSubsequence & lb, const mfecovar & x, const TUSubsequence & dr, const TUSubsequence & rb);
    mfecovar nil_l_r(const TUSubsequence & n);
    mfecovar sadd_l_r(const TUSubsequence & lb, const mfecovar & x);
    mfecovar sr_l_r(const TUSubsequence & lb, const mfecovar & x, const TUSubsequence & rb);


    String addss_r(const String & e, const TUSubsequence & rb);
    String bl_r(const TUSubsequence & lb, const TUSubsequence & lregion, const String & e, const TUSubsequence & rb);
    String br_r(const TUSubsequence & lb, const String & e, const TUSubsequence & rregion, const TUSubsequence & rb);
    String cadd_r(const String & le, const String & re);
    String drem_r(const TUSubsequence & lloc, const String & e, const TUSubsequence & rloc);
    String edl_r(const TUSubsequence & lb, const String & e, const TUSubsequence & loc);
    String edlr_r(const TUSubsequence & lb, const String & e, const TUSubsequence & rb);
    String edr_r(const TUSubsequence & loc, const String & e, const TUSubsequence & rb);
    List_Ref<String> h_r(List_Ref<String> i);
    String hl_r(const TUSubsequence & lb, const TUSubsequence & region, const TUSubsequence & rb);
    String il_r(const TUSubsequence & lb, const TUSubsequence & lregion, const String & e, const TUSubsequence & rregion, const TUSubsequence & rb);
    String incl_r(const String & e);
    String ml_r(const TUSubsequence & lb, const String & e, const TUSubsequence & rb);
    String mldl_r(const TUSubsequence & lb, const TUSubsequence & dl, const String & e, const TUSubsequence & rb);
    String mldlr_r(const TUSubsequence & lb, const TUSubsequence & dl, const String & e, const TUSubsequence & dr, const TUSubsequence & rb);
    String mldr_r(const TUSubsequence & lb, const String & e, const TUSubsequence & dr, const TUSubsequence & rb);
    String nil_r(const TUSubsequence & loc);
    String sadd_r(const TUSubsequence & lb, const String & e);
    String sr_r(const TUSubsequence & lb, const String & e, const TUSubsequence & rb);


 public:
   void cyk();

 public:
   List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  run()
{
  return nt_struct(t_0_left_most);
}
void print_stats(std::ostream &o)
{
#ifdef STATS
      o << "\n\nN = " << seq.size() << '\n';
      dangle_table.print_stats(o, "dangle_table");
      iloop_table.print_stats(o, "iloop_table");
      ml_comps_table.print_stats(o, "ml_comps_table");
      ml_comps1_table.print_stats(o, "ml_comps1_table");
      strong_table.print_stats(o, "strong_table");
      struct_table.print_stats(o, "struct_table");
      weak_table.print_stats(o, "weak_table");
#endif
}

template <typename Value>   void  print_result(std::ostream &out, Value& res)

{
if (isEmpty(res))
  out << "[]\n";
else
  out << res << '\n';

}
template <typename Value>   void  print_backtrack(std::ostream &out, Value& value)

{
}
   void  print_subopt(std::ostream &out, int  delta = 0) {}

};

#ifndef NO_GAPC_TYPEDEFS
namespace gapc {
  typedef shape5mfepp class_name;
  typedef List_Ref<std::pair<std::pair<Shape, mfecovar> , String> > &  return_type;
}
#endif

#endif

