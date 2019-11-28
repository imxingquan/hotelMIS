#!/usr/bin/perl

open (OUT0, ">custom.h");
open (OUT, ">custom-macros.h");

print OUT0 << "---";

// This file is generated from the perl script custom.pl, please do 
// not modify this file directly.

#ifndef MYSQLPP_CUSTOM_H
#define MYSQLPP_CUSTOM_H

#include "defs.h"
#include "tiny_int.h"

#include <string>

namespace mysqlpp {

enum sql_dummy_type {sql_dummy};

inline int sql_cmp(const std::string &a, const std::string &b) {
  return a.compare(b);
}
---

@types = ("char", "unsigned char", "tiny_int", "int", "unsigned int",
	  "short int", "unsigned short int");
foreach $type (@types) {
    print OUT0 << "---";

inline int sql_cmp($type a,$type b) {
  return a-b;
}
---
}

@types = ("double", "float");
foreach $type (@types) {
    print OUT0 << "---";

inline int sql_cmp($type a,$type b) {
  if (a == b) return 0;
  if (a <  b) return -1;
  return 1;
}
---
}	

@types = ("longlong", "ulonglong");
foreach $type (@types) {
    print OUT0 << "---";

inline int sql_cmp($type a,$type b) {
  if (a == b) return 0;
  if (a <  b) return -1;
  return 1;
}
---
}	

print OUT0 << "---";

#include "custom-macros.h"

} // end namespace mysqlpp

#endif

---

print OUT << "---";

// This file is generated from the perl script custom.pl, please do 
// not modify this file directly unless you wish to cut out unnessary
// macros.

// ---------------------------------------------------
//                Begin Mandatory Compare 
// ---------------------------------------------------

#define sql_compare_define(NAME) \\
    bool operator == (const NAME &other) const \\
      {return sql_compare_##NAME<sql_dummy>(*this,other) == 0;} \\
    bool operator != (const NAME &other) const \\
      {return sql_compare_##NAME<sql_dummy>(*this,other) != 0;} \\
    bool operator > (const NAME &other) const \\
      {return sql_compare_##NAME<sql_dummy>(*this,other) >  0;} \\
    bool operator < (const NAME &other) const \\
      {return sql_compare_##NAME<sql_dummy>(*this,other) <  0;} \\
    bool operator >= (const NAME &other) const \\
      {return sql_compare_##NAME<sql_dummy>(*this,other) >= 0;} \\
    bool operator <= (const NAME &other) const \\
      {return sql_compare_##NAME<sql_dummy>(*this,other) <= 0;} \\
    int cmp (const NAME &other) const \\
      {return sql_compare_##NAME<sql_dummy>(*this,other);} \\
    int compare (const NAME &other) const \\
      {return sql_compare_##NAME<sql_dummy>(*this,other);}
---

foreach $j (1..26) {
    $parm0 .= "T$j, C$j";
    $parm0 .= ", " unless $j == 26;
    $parm1 .= "C$j";
    $parm1 .= ", " unless $j == 26;
}

print OUT << "---";

#define sql_compare_define_0(NAME, $parm0)

#define sql_construct_define_0(NAME, $parm0)

#define sql_COMPARE__0(NAME, $parm1)

#define sql_compare_type_def_0(NAME, WHAT, NUM) \\
  sql_compare_type_def_##NUM (NAME, WHAT, NUM)

#define sql_compare_type_defe_0(NAME, WHAT, NUM) \\
  sql_compare_type_defe_##NUM (NAME, WHAT, NUM)

// ---------------------------------------------------
//                 End Mandatory Compare 
// ---------------------------------------------------
---

foreach $i (1..26) {
  $compr = ""; $parm2 = ""; $define = "";
  $compr = "    int cmp; \\\n" unless $i == 1;
  $compp = "";
  foreach $j (1..$i) {
      $compr .= "    if (cmp = sql_cmp(x.C$j , y.C$j )) return cmp; \\\n"
                                                              unless $j == $i;
      $compr .= "    return sql_cmp(x.C$j , y.C$j );"   if $j == $i;
      $parm2 .= "const T$j &p$j";
      $parm2 .= ", "  unless $j == $i;
      $define.= "C$j (p$j)";
      $define.= ", "  unless $j == $i;
      $set   .= "    C$j = p$j;\\\n";
      $compp .= "true";
      $compp .= ", " unless $j == $i;
  }
  print OUT << "---";

// ---------------------------------------------------
//                   Begin Compare $i
// ---------------------------------------------------

#define sql_compare_define_$i(NAME, $parm0) \\
  NAME ($parm2) : $define {} \\
  void set  ($parm2) { \\
$set \\
  } \\
  sql_compare_define(NAME)

#define sql_construct_define_$i(NAME, $parm0) \\
  void set  ($parm2) { \\
$set \\
  } \\
  NAME ($parm2) : $define {}

#define sql_compare_type_def_$i(NAME, WHAT, NUM) \\
  return WHAT##_list(d, m, $compp)

#define sql_compare_type_defe_$i(NAME, WHAT, NUM) \\
  return WHAT##_list(d, c, m, $compp)

#define sql_COMPARE__$i(NAME, $parm1) \\
  template <sql_dummy_type dummy> \\
  int sql_compare_##NAME (const NAME &x, const NAME &y) { \\
$compr \\
  } \\
  template <sql_dummy_type dummy> \\
  int compare (const NAME &x, const NAME &y) { \\
$compr \\
  }

// ---------------------------------------------------
//                   End Compare $i
// ---------------------------------------------------

---
}

print OUT << "---";
---


foreach $i (1..26) {
    $parm_complete = ""; 
    $parm_order = ""; $parm_order2c = "";
    $parm_simple = ""; $parm_simple2c = "";
    $parm_simple_b = ""; $parm_simple2c_b = "";
    $parm_names = ""; $parm_names2c = "";
    $defs = ""; $popul = ""; $parmc = ""; $parmC = "";
    $value_list = ""; $field_list = ""; $equal_list = "";
    $value_list_cus = ""; $cus_field_list = ""; $cus_equal_list = "";
    $create_bool = ""; $create_list = "";
    $cusparms1 = ""; $cusparms2 = ""; $cusparmsv = "";    
    $cusparms11 = ""; $cusparms22 = "";
    $names = "";$enums = "";
    foreach $j (1 .. $i) {
        $parm_complete .= "T$j, I$j, N$j, O$j";
	$parm_complete .= ", " unless $j == $i;
	$parm_order    .= "T$j, I$j, O$j";
	$parm_order    .= ", " unless $j == $i;
        $parm_order2c  .= "T$j, I$j, #I$j, O$j";
	$parm_order2c  .= ", " unless $j == $i;
        $parm_names    .= "T$j, I$j, N$j";
	$parm_names    .= ", " unless $j == $i;
	$parm_names2c  .= "T$j, I$j, N$j, ". ($j-1);
	$parm_names2c  .= ", " unless $j == $i;
	$parm_simple   .= "T$j, I$j";
	$parm_simple   .= ", " unless $j == $i;
	$parm_simple2c .= "T$j, I$j, #I$j, ". ($j-1);
	$parm_simple2c .= ", " unless $j == $i;
	$parm_simple_b   .= "T$j, I$j";
	$parm_simple_b   .= ", " unless $j == $i;
	$parm_simple2c_b .= "T$j, I$j, ". ($j-1);
	$parm_simple2c_b .= ", " unless $j == $i;
	$defs  .= "    T$j I$j;";
	$defs  .= "\n" unless $j == $i;
	$popul .= "    s->I$j = static_cast<T$j>(row[ O$j ]);";
	$popul .= "\n" unless $j == $i;
        $names .= "    N$j ";
	$names .= ",\n" unless $j == $i;
        $enums .= "    NAME##_##I$j";
	$enums .= ",\n" unless $j == $i;
        $field_list .= "    s << obj.manip << obj.obj->names[".($j-1)."]";
	$field_list .= " << obj.delem;\n" unless $j == $i;
	$value_list .= "    s << obj.manip << obj.obj->I$j";
	$value_list .= " << obj.delem;\n" unless $j == $i;
        $create_bool .= "    if (i$j) (*include)[".($j-1)."]=true;\n";
        $create_list .= "    if (i$j == NAME##_NULL) return;\n" unless $i == 1;
        $create_list .= "    (*include)[i$j]=true;\n";

        $value_list_cus .= "    if ((*obj.include)[".($j-1)."]) { \n";
	$value_list_cus .= "      if (before) s << obj.delem;\n" unless $j == 1;
        $value_list_cus .= "      s << obj.manip << obj.obj->I$j;\n";
	$value_list_cus .= "      before = true; \n" unless $j == $i;
	$value_list_cus .= "     } \n";

        $cus_field_list .= "    if ((*obj.include)[".($j-1)."]) { \n";
	$cus_field_list .= "      if (before) s << obj.delem;\n" unless $j == 1;
        $cus_field_list .= "      s << obj.manip << obj.obj->names[".($j-1)."];\n";
	$cus_field_list .= "      before = true; \n" unless $j == $i;
	$cus_field_list .= "     } \n";

        $cus_equal_list .= "    if ((*obj.include)[".($j-1)."]) { \n";
	$cus_equal_list .= "      if (before) s << obj.delem;\n" unless $j == 1;
        $cus_equal_list .= "      s << obj.obj->names[".($j-1)."] << obj.comp";
        $cus_equal_list .=        " << obj.manip << obj.obj->I$j;\n";
	$cus_equal_list .= "      before = true; \n" unless $j == $i;
	$cus_equal_list .= "     } \n";

        $equal_list .= "    s << obj.obj->names[".($j-1)."] << obj.comp";
        $equal_list .= " << obj.manip << obj.obj->I$j";
	$equal_list .= " << obj.delem;\n" unless $j == $i;
        $cusparms1  .= "bool i$j"         if     $j == 1;
	$cusparms1  .= "bool i$j = false" unless $j == 1;
	$cusparms1  .= ", " unless $j == $i;
        $cusparms11  .= "bool i$j" ;
	$cusparms11  .= ", " unless $j == $i;
	$cusparms2  .= "NAME##_enum i$j" if $j == 1;
	$cusparms2  .= "NAME##_enum i$j = NAME##_NULL" unless $j == 1;
	$cusparms2  .= ", " unless $j == $i;
	$cusparms22  .= "NAME##_enum i$j";
	$cusparms22  .= ", " unless $j == $i;
        $cusparmsv  .= "i$j";
	$cusparmsv  .= ", " unless $j == $i;
	$parmC .= "T$j, I$j";
	$parmC .= ", " unless $j == 26;
        $parmc .= "I$j";
	$parmc .= ", " unless $j == 26;
    }
    foreach $j ($i+1 .. 26) {
	$parmC .= "0, 0";
	$parmC .= ", " unless $j == 26;
        $parmc .= "0";
	$parmc .= ", " unless $j == 26;
    }

    print OUT << "---";
// ---------------------------------------------------
//                  Begin Create $i
// ---------------------------------------------------
---
    $out = <<"---";
#define sql_create_basic_c_order_$i(NAME, CMP, CONTR, $parm_order)

  struct NAME; 

  template <sql_dummy_type dummy> int sql_compare_##NAME (const NAME &, const NAME &);

  struct NAME { 
$defs 
    NAME () {} 
    NAME (const Row &row);
    sql_compare_define_##CMP(NAME, $parmC)
  }; 

  template <sql_dummy_type dummy> 
    void populate_##NAME (NAME *s, const Row &row) { 
$popul 
  } 

  inline NAME::NAME (const Row &row) 
    {populate_##NAME<sql_dummy>(this, row);} 

  sql_COMPARE__##CMP(NAME, $parmc )
---
    print OUT &prepare($out);

    $out = <<"---";
#define sql_create_complete_$i(NAME, CMP, CONTR, $parm_complete) 
  struct NAME; 

  enum NAME##_enum { 
$enums 
    ,NAME##_NULL 
  }; 

  template <class Manip>
  class NAME##_value_list { 
  /*friend std::ostream& operator << <> (std::ostream&, const NAME##_value_list&); */
  public: 
    const NAME *obj;
    cchar *delem;
    Manip manip;
  public: 
    NAME##_value_list (const NAME *o, cchar *d, Manip m) 
      : obj(o), delem(d), manip(m) {} 
  };

  template <class Manip>
  class NAME##_##field_list {
  /* friend std::ostream& operator << <> (std::ostream&, const NAME##_field_list&); */
  public: 
    const NAME *obj; 
    cchar *delem;
    Manip manip;
  public: 
    NAME##_field_list (const NAME *o, cchar *d, Manip m) 
      : obj(o), delem(d), manip(m) {} 
  };

  template <class Manip>
  class NAME##_equal_list { 
  /* friend std::ostream& operator << <> (std::ostream&, const NAME##_equal_list&); */
  public: 
    const NAME *obj;
    cchar *delem;
    cchar *comp;
    Manip manip;
  public: 
    NAME##_equal_list (const NAME *o, cchar *d, cchar *c, Manip m) 
      : obj(o), delem(d), comp(c), manip(m) {}
  };

  template <class Manip>
  class NAME##_cus_value_list {
  /* friend std::ostream& operator << <> (std::ostream&, 
  				  const NAME##_cus_value_list<Manip>&); */
  public:
    const NAME *obj;
    cchar *delem;
    Manip manip;
    std::vector<bool> *include;
    bool del_vector;
  public: 
    ~NAME##_cus_value_list () {if (del_vector) delete include;} 
    NAME##_cus_value_list (const NAME *o, cchar *d, Manip m, $cusparms11);
    NAME##_cus_value_list (const NAME *o, cchar *d, Manip m, $cusparms22); 
    NAME##_cus_value_list (const NAME *o, cchar *d, Manip m ,std::vector<bool>* i)
      : obj(o), include(i), del_vector(false), delem(d), manip(m) {}
  };

  template <class Manip>
  class NAME##_cus_field_list { 
  /* friend std::ostream& operator << <> (std::ostream&, 
     				  const NAME##_cus_field_list<Manip>&); */
  public:
    const NAME *obj; 
    cchar *delem;
    Manip manip;
    std::vector<bool> *include; 
    bool del_vector; 
  public: 
    ~NAME##_cus_field_list () {if (del_vector) delete include;} 
    NAME##_cus_field_list (const NAME *o, cchar *d, Manip m, $cusparms11); 
    NAME##_cus_field_list (const NAME *o, cchar *d, Manip m, $cusparms22); 
    NAME##_cus_field_list (const NAME *o, cchar *d, Manip m, std::vector<bool> *i) 
      : obj(o), include(i), del_vector(false), delem(d), manip(m) {}
  };

 template <class Manip>
 class NAME##_cus_equal_list {
 /* friend std::ostream& operator << <> (std::ostream&, 
				  const NAME##_cus_equal_list<Manip>&); */
  public:
    const NAME *obj;
    std::vector<bool> *include;
    bool del_vector;
    cchar *delem;
    cchar *comp;
    Manip manip;
  public:
    ~NAME##_##cus_equal_list () {if (del_vector) delete include;}
    NAME##_##cus_equal_list (const NAME *o, cchar *d, cchar *c, Manip m, $cusparms11); 
    NAME##_##cus_equal_list (const NAME *o, cchar *d, cchar *c, Manip m, $cusparms22); 
    NAME##_##cus_equal_list (const NAME *o, cchar *d, cchar *c, Manip m, std::vector<bool> *i) 
      : obj(o), include(i), del_vector(false), delem(d), comp(c), manip(m) {}
  };

  template <sql_dummy_type dummy> int sql_compare_##NAME (const NAME &, const NAME &);

  struct NAME { 
$defs 
    NAME () {} 
    NAME (const Row &row);
    void set (const Row &row);
    sql_compare_define_##CMP(NAME, $parmC)
    sql_construct_define_##CONTR(NAME, $parmC)
    static const char *names[];
    static const char *_table;
    static const char *& table() {return _table;}

    NAME##_value_list<quote_type0> value_list() const {
      return value_list(",", quote);}
    NAME##_value_list<quote_type0> value_list(cchar *d) const {
      return value_list(d, quote);}
    template <class Manip> 
    NAME##_value_list<Manip> value_list(cchar *d, Manip m) const; 

    NAME##_field_list<do_nothing_type0> field_list() const {
      return field_list(",", do_nothing);}
    NAME##_field_list<do_nothing_type0> field_list(cchar *d) const {
      return field_list(d, do_nothing);}
    template <class Manip>
    NAME##_field_list<Manip> field_list(cchar *d, Manip m) const; 

    NAME##_equal_list<quote_type0> equal_list(cchar *d = ",", 
                                              cchar *c = " = ") const{
      return equal_list(d, c, quote);}
    template <class Manip>
    NAME##_equal_list<Manip> equal_list(cchar *d, cchar *c, Manip m) const; 
    
    /* cus_data */

    NAME##_cus_value_list<quote_type0> value_list($cusparms1) const {
      return value_list(",", quote, $cusparmsv);
    }
    NAME##_cus_value_list<quote_type0> value_list($cusparms2) const {
      return value_list(",", quote, $cusparmsv);
    }
    NAME##_cus_value_list<quote_type0> value_list(std::vector<bool> *i) const {
      return value_list(",", quote, i);
    }
    NAME##_cus_value_list<quote_type0> value_list(sql_cmp_type sc) const {
      return value_list(",", quote, sc);
    }

    NAME##_cus_value_list<quote_type0> value_list(cchar *d, $cusparms1) const {
      return value_list(d, quote, $cusparmsv);
    }
    NAME##_cus_value_list<quote_type0> value_list(cchar *d, $cusparms2) const {
      return value_list(d, quote, $cusparmsv);
    }
    NAME##_cus_value_list<quote_type0> value_list(cchar *d, 
						std::vector<bool> *i) const {
      return value_list(d, quote, i);
    }
    NAME##_cus_value_list<quote_type0> value_list(cchar *d, 
						sql_cmp_type sc) const {
      return value_list(d, quote, sc);
    }

    template <class Manip>
    NAME##_cus_value_list<Manip> value_list(cchar *d, Manip m,
					  $cusparms1) const; 
    template <class Manip>
    NAME##_cus_value_list<Manip> value_list(cchar *d, Manip m,
					  $cusparms2) const; 
    template <class Manip>
    NAME##_cus_value_list<Manip> value_list(cchar *d, Manip m, 
					  std::vector<bool> *i) const;
    template <class Manip>
    NAME##_cus_value_list<Manip> value_list(cchar *d, Manip m, 
					  sql_cmp_type sc) const;
    /* cus field */

    NAME##_cus_field_list<do_nothing_type0> field_list($cusparms1) const {
      return field_list(",", do_nothing, $cusparmsv);
    }
    NAME##_cus_field_list<do_nothing_type0> field_list($cusparms2) const {
      return field_list(",", do_nothing, $cusparmsv);
    }
    NAME##_cus_field_list<do_nothing_type0> field_list(std::vector<bool> *i) const {
      return field_list(",", do_nothing, i);
    }
    NAME##_cus_field_list<do_nothing_type0> field_list(sql_cmp_type sc) const
    {
      return field_list(",", do_nothing, sc);
    }

    NAME##_cus_field_list<do_nothing_type0> field_list(cchar *d, 
						       $cusparms1) const {
      return field_list(d, do_nothing, $cusparmsv);
    }
    NAME##_cus_field_list<do_nothing_type0> field_list(cchar *d,
						       $cusparms2) const {
      return field_list(d, do_nothing, $cusparmsv);
    }
    NAME##_cus_field_list<do_nothing_type0> field_list(cchar *d, 
						std::vector<bool> *i) const {
      return field_list(d, do_nothing, i);
    }
    NAME##_cus_field_list<do_nothing_type0> field_list(cchar *d, 
						sql_cmp_type sc) const {
      return field_list(d, do_nothing, sc);
    }

    template <class Manip>
    NAME##_cus_field_list<Manip> field_list(cchar *d, Manip m,
					    $cusparms1) const; 
    template <class Manip>
    NAME##_cus_field_list<Manip> field_list(cchar *d, Manip m,
					    $cusparms2) const; 
    template <class Manip>
    NAME##_cus_field_list<Manip> field_list(cchar *d, Manip m,
					    std::vector<bool> *i) const;
    template <class Manip>
    NAME##_cus_field_list<Manip> field_list(cchar *d, Manip m, 
					    sql_cmp_type sc) const;

    /* cus equal */

    NAME##_cus_equal_list<quote_type0> equal_list($cusparms1) const {
      return equal_list(",", " = ", quote, $cusparmsv);
    }
    NAME##_cus_equal_list<quote_type0> equal_list($cusparms2) const {
      return equal_list(",", " = ", quote, $cusparmsv);
    }
    NAME##_cus_equal_list<quote_type0> equal_list(std::vector<bool> *i) const {
      return equal_list(",", " = ", quote, i);
    }
    NAME##_cus_equal_list<quote_type0> equal_list(sql_cmp_type sc) const {
      return equal_list(",", " = ", quote, sc);
    }

    NAME##_cus_equal_list<quote_type0> equal_list(cchar *d, $cusparms1) const {
      return equal_list(d, " = ", quote, $cusparmsv);
    }
    NAME##_cus_equal_list<quote_type0> equal_list(cchar *d, $cusparms2) const {
      return equal_list(d, " = ", quote, $cusparmsv);
    }
    NAME##_cus_equal_list<quote_type0> equal_list(cchar *d, 
						std::vector<bool> *i) const {
      return equal_list(d, " = ", quote, i);
    }
    NAME##_cus_equal_list<quote_type0> equal_list(cchar *d, 
						sql_cmp_type sc) const {
      return equal_list(d, " = ", quote, sc);
    }

    NAME##_cus_equal_list<quote_type0> equal_list(cchar *d, cchar *c,
                                                $cusparms1) const {
      return equal_list(d, c, quote, $cusparmsv);
    }
    NAME##_cus_equal_list<quote_type0> equal_list(cchar *d, cchar *c,
                                                $cusparms2) const {
      return equal_list(d, c, quote, $cusparmsv);
    }
    NAME##_cus_equal_list<quote_type0> equal_list(cchar *d, cchar *c,
						std::vector<bool> *i) const {
      return equal_list(d, c, quote, i);
    }
    NAME##_cus_equal_list<quote_type0> equal_list(cchar *d, cchar *c,
						sql_cmp_type sc) const {
      return equal_list(d, c, quote, sc);
    }

    template <class Manip>
    NAME##_cus_equal_list<Manip> equal_list(cchar *d, cchar *c, Manip m, 
					    $cusparms1) const; 
    template <class Manip>
    NAME##_cus_equal_list<Manip> equal_list(cchar *d, cchar *c, Manip m, 
					    $cusparms2) const; 
    template <class Manip>
    NAME##_cus_equal_list<Manip> equal_list(cchar *d, cchar *c, Manip m, 
					    std::vector<bool> *i) const;
    template <class Manip>
    NAME##_cus_equal_list<Manip> equal_list(cchar *d, cchar *c, Manip m, 
					    sql_cmp_type sc) const;
  }; 

  const char *NAME::names[] = { 
$names 
  }; 
  const char *NAME::_table = #NAME ;  

  template <class Manip>
  NAME##_cus_value_list<Manip>::NAME##_cus_value_list
  (const NAME *o, cchar *d, Manip m, $cusparms11) 
  { 
    delem = d;
    manip = m;
    del_vector = true;
    obj = o; 
    include = new std::vector<bool>($i, false);
$create_bool 
  } 

  template <class Manip>
  NAME##_cus_value_list<Manip>::NAME##_cus_value_list
  (const NAME *o, cchar *d, Manip m, $cusparms22) { 
    delem = d;
    manip = m;
    del_vector = true; 
    obj = o; 
    include = new std::vector<bool>($i, false); 
$create_list 
  }

  template <class Manip>
  NAME##_cus_field_list<Manip>::NAME##_cus_field_list
  (const NAME *o, cchar *d, Manip m, $cusparms11) {
    delem = d;
    manip = m;
    del_vector = true; 
    obj = o; 
    include = new std::vector<bool>($i, false); 
$create_bool 
  } 

  template <class Manip>
  NAME##_cus_field_list<Manip>::NAME##_cus_field_list
  (const NAME *o, cchar *d, Manip m, $cusparms22) { 
    delem = d;
    manip = m;
    del_vector = true; 
    obj = o; 
    include = new std::vector<bool>($i, false); 
$create_list 
  }

  template <class Manip>
  NAME##_cus_equal_list<Manip>::NAME##_cus_equal_list
  (const NAME *o, cchar *d, cchar *c, Manip m, $cusparms11) { 
    delem = d;
    comp = c;
    manip = m;
    del_vector = true; 
    obj = o; 
    include = new std::vector<bool>($i, false); 
$create_bool 
  } 

  template <class Manip>
  NAME##_cus_equal_list<Manip>::NAME##_cus_equal_list
  (const NAME *o, cchar *d, cchar *c, Manip m, $cusparms22) { 
    delem = d;
    comp = c;
    manip = m;
    del_vector = true; 
    obj = o; 
    include = new std::vector<bool>($i, false); 
$create_list 
  }

  template <class Manip>
  std::ostream& operator << (std::ostream& s, const NAME##_value_list<Manip>& obj) { 
$value_list; 
    return s; 
  } 

  template <class Manip>
  std::ostream& operator << (std::ostream& s, const NAME##_field_list<Manip>& obj) { 
$field_list; 
    return s; 
  } 

  template <class Manip>
  std::ostream& operator << (std::ostream& s, const NAME##_equal_list<Manip>& obj) { 
$equal_list; 
    return s; 
  } 

  template <class Manip>
  std::ostream& operator << (std::ostream& s, const NAME##_cus_value_list<Manip>& obj) { 
    bool before = false; 
$value_list_cus 
    return s; 
  } 

  template <class Manip>
  std::ostream& operator << (std::ostream& s, const NAME##_cus_field_list<Manip>& obj) { 
    bool before = false; 
$cus_field_list 
    return s; 
  } 

  template <class Manip>
  std::ostream& operator << (std::ostream& s, const NAME##_cus_equal_list<Manip>& obj) { 
    bool before = false; 
$cus_equal_list 
    return s; 
  } 

  template <class Manip>
  inline NAME##_value_list<Manip> NAME::value_list(cchar *d, Manip m) const { 
    return NAME##_value_list<Manip> (this, d, m); 
  } 

  template <class Manip>
  inline NAME##_field_list<Manip> NAME::field_list(cchar *d, Manip m) const { 
    return NAME##_field_list<Manip> (this, d, m); 
  } 

  template <class Manip>
  inline NAME##_equal_list<Manip> NAME::equal_list(cchar *d, cchar *c, Manip m) const { 
    return NAME##_equal_list<Manip> (this, d, c, m); 
  } 
 
  template <class Manip>
  inline NAME##_cus_value_list<Manip> NAME::value_list(cchar *d, Manip m,
						       $cusparms11) const {
    return NAME##_cus_value_list<Manip> (this, d, m, $cusparmsv); 
  } 

  template <class Manip>
  inline NAME##_cus_field_list<Manip> NAME::field_list(cchar *d, Manip m,
							 $cusparms11) const { 
    return NAME##_cus_field_list<Manip> (this, d, m, $cusparmsv); 
  } 

  template <class Manip>
  inline NAME##_cus_equal_list<Manip> NAME::equal_list(cchar *d, cchar *c, Manip m,
							 $cusparms11) const { 
    return NAME##_cus_equal_list<Manip> (this, d, c, m, $cusparmsv); 
  } 

  template <class Manip>
  inline NAME##_cus_value_list<Manip> NAME::value_list(cchar *d, Manip m,
						       $cusparms22) const { 
    return NAME##_cus_value_list<Manip> (this, d, m, $cusparmsv); 
  } 

  template <class Manip>
  inline NAME##_cus_field_list<Manip> NAME::field_list(cchar *d, Manip m,
							 $cusparms22) const {
    return NAME##_cus_field_list<Manip> (this, d, m, $cusparmsv); 
  } 

  template <class Manip>
  inline NAME##_cus_equal_list<Manip> NAME::equal_list(cchar *d, cchar *c, Manip m, 
							 $cusparms22) const { 
    return NAME##_cus_equal_list<Manip> (this, d, c, m, $cusparmsv); 
  } 

  template <class Manip>
  inline NAME##_cus_value_list<Manip> 
  NAME::value_list(cchar *d, Manip m, sql_cmp_type /*sc*/) const {
    sql_compare_type_def_##CMP (NAME, value, NUM);
  }

  template <class Manip>
  inline NAME##_cus_field_list<Manip> 
  NAME::field_list(cchar *d, Manip m, sql_cmp_type /*sc*/) const {
    sql_compare_type_def_##CMP (NAME, field, NUM);
  }

  template <class Manip>
  inline NAME##_cus_equal_list<Manip> 
  NAME::equal_list(cchar *d, cchar *c, Manip m, sql_cmp_type /*sc*/) const {
    sql_compare_type_defe_##CMP (NAME, equal, NUM);
  }

  template <sql_dummy_type dummy> 
  void populate_##NAME (NAME *s, const Row &row) { 
$popul
  } 

  inline NAME::NAME (const Row &row) 
                                        {populate_##NAME<sql_dummy>(this, row);}
  inline void NAME::set (const Row &row)
                                        {populate_##NAME<sql_dummy>(this, row);}

  sql_COMPARE__##CMP(NAME, $parmc )

---
print OUT &prepare($out);

#
# short cut defs
#

print OUT << "---";
#define sql_create_basic_$i(NAME, CMP, CONTR, $parm_simple_b) \\
  sql_create_basic_c_order_$i(NAME, CMP, CONTR, $parm_simple2c_b)

#define sql_create_$i(NAME, CMP, CONTR, $parm_simple) \\
  sql_create_complete_$i(NAME, CMP, CONTR, $parm_simple2c) \\

#define sql_create_c_order_$i(NAME, CMP, CONTR, $parm_order) \\
  sql_create_complete_$i(NAME, CMP, CONTR, $parm_order2c)

#define sql_create_c_names_$i(NAME, CMP, CONTR, $parm_names) \\
  sql_create_complete_$i(NAME, CMP, CONTR, $parm_names2c)

// ---------------------------------------------------
//                  End Create $i
// ---------------------------------------------------

---

}


sub prepare {
    local $_ = @_[0];
    s/\n+$//;
    s/\n[\n ]*\n/\n/g; 
    s/\n+/\\\n/g;
    $_ .= "\n\n";
    return $_;
}

