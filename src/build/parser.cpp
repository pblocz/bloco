// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.
#line 2 "parser.yy" // lalr1.cc:399

#include <iostream>
#include <string>
#include <vector>

#include "nodes.hpp"

#line 44 "build/parser.cpp" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.hpp"

// User implementation prologue.
#line 65 "parser.yy" // lalr1.cc:407

#include "blocodriver.hpp"
#include "scanner.hpp"

/* connect bison parser to flex scanner in the driver, the function to get the
 * next token.
 */
#undef yylex
#define yylex driver.lexer->lex

#line 68 "build/parser.cpp" // lalr1.cc:407


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 20 "parser.yy" // lalr1.cc:474
namespace parser {
#line 154 "build/parser.cpp" // lalr1.cc:474

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (bloco::BlocoDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
     : type (empty)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 51: // program

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 373 "build/parser.cpp" // lalr1.cc:599
        break;

      case 52: // stmt_list

#line 62 "parser.yy" // lalr1.cc:599
        { for(auto n: *(yysym.value.vect)) n->loc = yysym.location; }
#line 380 "build/parser.cpp" // lalr1.cc:599
        break;

      case 53: // stmt

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 387 "build/parser.cpp" // lalr1.cc:599
        break;

      case 54: // expr15

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 394 "build/parser.cpp" // lalr1.cc:599
        break;

      case 55: // expr14

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 401 "build/parser.cpp" // lalr1.cc:599
        break;

      case 56: // expr14_1

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 408 "build/parser.cpp" // lalr1.cc:599
        break;

      case 57: // expr14_2

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 415 "build/parser.cpp" // lalr1.cc:599
        break;

      case 58: // expr13

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 422 "build/parser.cpp" // lalr1.cc:599
        break;

      case 59: // expr12

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 429 "build/parser.cpp" // lalr1.cc:599
        break;

      case 60: // expr11

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 436 "build/parser.cpp" // lalr1.cc:599
        break;

      case 61: // expr10

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 443 "build/parser.cpp" // lalr1.cc:599
        break;

      case 62: // expr9

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 450 "build/parser.cpp" // lalr1.cc:599
        break;

      case 63: // expr8

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 457 "build/parser.cpp" // lalr1.cc:599
        break;

      case 64: // expr7

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 464 "build/parser.cpp" // lalr1.cc:599
        break;

      case 65: // expr6

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 471 "build/parser.cpp" // lalr1.cc:599
        break;

      case 66: // expr5

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 478 "build/parser.cpp" // lalr1.cc:599
        break;

      case 67: // expr4

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 485 "build/parser.cpp" // lalr1.cc:599
        break;

      case 68: // expr3

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 492 "build/parser.cpp" // lalr1.cc:599
        break;

      case 69: // expr1

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 499 "build/parser.cpp" // lalr1.cc:599
        break;

      case 70: // lista_args

#line 62 "parser.yy" // lalr1.cc:599
        { for(auto n: *(yysym.value.vect)) n->loc = yysym.location; }
#line 506 "build/parser.cpp" // lalr1.cc:599
        break;

      case 71: // funcion_anonima

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 513 "build/parser.cpp" // lalr1.cc:599
        break;

      case 72: // declaracion

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 520 "build/parser.cpp" // lalr1.cc:599
        break;

      case 73: // type

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 527 "build/parser.cpp" // lalr1.cc:599
        break;

      case 74: // lista_types

#line 62 "parser.yy" // lalr1.cc:599
        { for(auto n: *(yysym.value.vect)) n->loc = yysym.location; }
#line 534 "build/parser.cpp" // lalr1.cc:599
        break;

      case 75: // lista_types_nombre

#line 63 "parser.yy" // lalr1.cc:599
        { for(auto n: *(yysym.value.vectnom)) n.first->loc = yysym.location; }
#line 541 "build/parser.cpp" // lalr1.cc:599
        break;

      case 76: // def_funcion_cte

#line 61 "parser.yy" // lalr1.cc:599
        { (yysym.value.nodeptr)->loc = yysym.location; }
#line 548 "build/parser.cpp" // lalr1.cc:599
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 23 "parser.yy" // lalr1.cc:725
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 684 "build/parser.cpp" // lalr1.cc:725

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 82 "parser.yy" // lalr1.cc:847
    {driver.tree.setnode(new NodeProg((yystack_[0].value.vect)));}
#line 798 "build/parser.cpp" // lalr1.cc:847
    break;

  case 3:
#line 87 "parser.yy" // lalr1.cc:847
    {
        (yystack_[1].value.vect)->push_back((yystack_[0].value.nodeptr));
        (yylhs.value.vect)=(yystack_[1].value.vect);}
#line 806 "build/parser.cpp" // lalr1.cc:847
    break;

  case 4:
#line 90 "parser.yy" // lalr1.cc:847
    {
    auto aux=new NodeList();
    aux->push_back((yystack_[0].value.nodeptr));
    (yylhs.value.vect)=aux;}
#line 815 "build/parser.cpp" // lalr1.cc:847
    break;

  case 5:
#line 98 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[1].value.nodeptr);}
#line 821 "build/parser.cpp" // lalr1.cc:847
    break;

  case 6:
#line 99 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[1].value.nodeptr);}
#line 827 "build/parser.cpp" // lalr1.cc:847
    break;

  case 7:
#line 100 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 833 "build/parser.cpp" // lalr1.cc:847
    break;

  case 8:
#line 108 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario(',',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 839 "build/parser.cpp" // lalr1.cc:847
    break;

  case 9:
#line 109 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('\'',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 845 "build/parser.cpp" // lalr1.cc:847
    break;

  case 10:
#line 110 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 851 "build/parser.cpp" // lalr1.cc:847
    break;

  case 11:
#line 122 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('=',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 857 "build/parser.cpp" // lalr1.cc:847
    break;

  case 12:
#line 123 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('=',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 863 "build/parser.cpp" // lalr1.cc:847
    break;

  case 13:
#line 124 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('@',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 869 "build/parser.cpp" // lalr1.cc:847
    break;

  case 14:
#line 125 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('@',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 875 "build/parser.cpp" // lalr1.cc:847
    break;

  case 15:
#line 126 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 881 "build/parser.cpp" // lalr1.cc:847
    break;

  case 16:
#line 127 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 887 "build/parser.cpp" // lalr1.cc:847
    break;

  case 17:
#line 135 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('?',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 893 "build/parser.cpp" // lalr1.cc:847
    break;

  case 18:
#line 136 "parser.yy" // lalr1.cc:847
    {
		NodeList *v=new NodeList;
		v->push_back((yystack_[4].value.nodeptr));
		v->push_back((yystack_[2].value.nodeptr));
		v->push_back((yystack_[0].value.nodeptr));
		(yylhs.value.nodeptr)=new NodeExprOp('?', v);
	}
#line 905 "build/parser.cpp" // lalr1.cc:847
    break;

  case 19:
#line 143 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('?',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 911 "build/parser.cpp" // lalr1.cc:847
    break;

  case 20:
#line 147 "parser.yy" // lalr1.cc:847
    {
		NodeList *v=new NodeList;
		v->push_back((yystack_[4].value.nodeptr));
		v->push_back((yystack_[2].value.nodeptr));
		v->push_back((yystack_[0].value.nodeptr));
		(yylhs.value.nodeptr)=new NodeExprOp('?', v);
	}
#line 923 "build/parser.cpp" // lalr1.cc:847
    break;

  case 21:
#line 154 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 929 "build/parser.cpp" // lalr1.cc:847
    break;

  case 22:
#line 159 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario(barrabarra,(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 935 "build/parser.cpp" // lalr1.cc:847
    break;

  case 23:
#line 160 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 941 "build/parser.cpp" // lalr1.cc:847
    break;

  case 24:
#line 164 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario(andand,(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 947 "build/parser.cpp" // lalr1.cc:847
    break;

  case 25:
#line 165 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 953 "build/parser.cpp" // lalr1.cc:847
    break;

  case 26:
#line 169 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('|',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 959 "build/parser.cpp" // lalr1.cc:847
    break;

  case 27:
#line 170 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 965 "build/parser.cpp" // lalr1.cc:847
    break;

  case 28:
#line 174 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('^',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 971 "build/parser.cpp" // lalr1.cc:847
    break;

  case 29:
#line 175 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 977 "build/parser.cpp" // lalr1.cc:847
    break;

  case 30:
#line 179 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('&',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 983 "build/parser.cpp" // lalr1.cc:847
    break;

  case 31:
#line 180 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 989 "build/parser.cpp" // lalr1.cc:847
    break;

  case 32:
#line 184 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario(igualigual,(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 995 "build/parser.cpp" // lalr1.cc:847
    break;

  case 33:
#line 185 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario(noigual,(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1001 "build/parser.cpp" // lalr1.cc:847
    break;

  case 34:
#line 186 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 1007 "build/parser.cpp" // lalr1.cc:847
    break;

  case 35:
#line 190 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario(menorigual,(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1013 "build/parser.cpp" // lalr1.cc:847
    break;

  case 36:
#line 191 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario(mayorigual,(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1019 "build/parser.cpp" // lalr1.cc:847
    break;

  case 37:
#line 192 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('<',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1025 "build/parser.cpp" // lalr1.cc:847
    break;

  case 38:
#line 193 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('>',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1031 "build/parser.cpp" // lalr1.cc:847
    break;

  case 39:
#line 194 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 1037 "build/parser.cpp" // lalr1.cc:847
    break;

  case 40:
#line 198 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario(menormenor,(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1043 "build/parser.cpp" // lalr1.cc:847
    break;

  case 41:
#line 199 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario(mayormayor,(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1049 "build/parser.cpp" // lalr1.cc:847
    break;

  case 42:
#line 200 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 1055 "build/parser.cpp" // lalr1.cc:847
    break;

  case 43:
#line 204 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('+',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1061 "build/parser.cpp" // lalr1.cc:847
    break;

  case 44:
#line 205 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('-',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1067 "build/parser.cpp" // lalr1.cc:847
    break;

  case 45:
#line 206 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 1073 "build/parser.cpp" // lalr1.cc:847
    break;

  case 46:
#line 210 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('*',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1079 "build/parser.cpp" // lalr1.cc:847
    break;

  case 47:
#line 211 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('/',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1085 "build/parser.cpp" // lalr1.cc:847
    break;

  case 48:
#line 212 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario('%',(yystack_[2].value.nodeptr),(yystack_[0].value.nodeptr));}
#line 1091 "build/parser.cpp" // lalr1.cc:847
    break;

  case 49:
#line 213 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 1097 "build/parser.cpp" // lalr1.cc:847
    break;

  case 50:
#line 221 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opunario(masmas,(yystack_[0].value.nodeptr));}
#line 1103 "build/parser.cpp" // lalr1.cc:847
    break;

  case 51:
#line 222 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opunario(menosmenos,(yystack_[0].value.nodeptr));}
#line 1109 "build/parser.cpp" // lalr1.cc:847
    break;

  case 52:
#line 223 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opunario('-',(yystack_[0].value.nodeptr));}
#line 1115 "build/parser.cpp" // lalr1.cc:847
    break;

  case 53:
#line 224 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opunario('+',(yystack_[0].value.nodeptr));}
#line 1121 "build/parser.cpp" // lalr1.cc:847
    break;

  case 54:
#line 225 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opunario('!',(yystack_[0].value.nodeptr));}
#line 1127 "build/parser.cpp" // lalr1.cc:847
    break;

  case 55:
#line 226 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opunario('~',(yystack_[0].value.nodeptr));}
#line 1133 "build/parser.cpp" // lalr1.cc:847
    break;

  case 56:
#line 227 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opunario('r',(yystack_[0].value.nodeptr));}
#line 1139 "build/parser.cpp" // lalr1.cc:847
    break;

  case 57:
#line 228 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opunario('c',(yystack_[0].value.nodeptr));}
#line 1145 "build/parser.cpp" // lalr1.cc:847
    break;

  case 58:
#line 229 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opunario('b',(yystack_[0].value.nodeptr));}
#line 1151 "build/parser.cpp" // lalr1.cc:847
    break;

  case 59:
#line 230 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 1157 "build/parser.cpp" // lalr1.cc:847
    break;

  case 60:
#line 234 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario(masmas,(yystack_[1].value.nodeptr),nullptr);}
#line 1163 "build/parser.cpp" // lalr1.cc:847
    break;

  case 61:
#line 235 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=opbinario(menosmenos,(yystack_[1].value.nodeptr),nullptr);}
#line 1169 "build/parser.cpp" // lalr1.cc:847
    break;

  case 62:
#line 236 "parser.yy" // lalr1.cc:847
    { //llamada a función
		auto aux=opunario('(', (yystack_[3].value.nodeptr));
		for(auto i:*(yystack_[1].value.vect)) ((NodeExprOp *)aux)->args->push_back(i);
		(yylhs.value.nodeptr)=aux;
	}
#line 1179 "build/parser.cpp" // lalr1.cc:847
    break;

  case 63:
#line 241 "parser.yy" // lalr1.cc:847
    {
		(yylhs.value.nodeptr)=opbinario('[', (yystack_[3].value.nodeptr), (yystack_[1].value.nodeptr));
	}
#line 1187 "build/parser.cpp" // lalr1.cc:847
    break;

  case 64:
#line 244 "parser.yy" // lalr1.cc:847
    { (yylhs.value.nodeptr)=opbinario('.', (yystack_[2].value.nodeptr), new NodeExprId(*(yystack_[0].value.stringval)));}
#line 1193 "build/parser.cpp" // lalr1.cc:847
    break;

  case 65:
#line 245 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=new NodeExprId(*(yystack_[0].value.stringval));}
#line 1199 "build/parser.cpp" // lalr1.cc:847
    break;

  case 66:
#line 246 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[0].value.nodeptr);}
#line 1205 "build/parser.cpp" // lalr1.cc:847
    break;

  case 67:
#line 247 "parser.yy" // lalr1.cc:847
    {
		(yylhs.value.nodeptr)=new NodeExprDefArr((yystack_[3].value.nodeptr),(yystack_[1].value.nodeptr));
	}
#line 1213 "build/parser.cpp" // lalr1.cc:847
    break;

  case 68:
#line 250 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=new NodeExprCte((yystack_[0].value.intval));}
#line 1219 "build/parser.cpp" // lalr1.cc:847
    break;

  case 69:
#line 251 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=(yystack_[1].value.nodeptr);}
#line 1225 "build/parser.cpp" // lalr1.cc:847
    break;

  case 70:
#line 255 "parser.yy" // lalr1.cc:847
    {(yylhs.value.vect)=new vector<Node *>();}
#line 1231 "build/parser.cpp" // lalr1.cc:847
    break;

  case 71:
#line 256 "parser.yy" // lalr1.cc:847
    { (yylhs.value.vect)=new vector<Node *>(); (yylhs.value.vect)->push_back((yystack_[0].value.nodeptr)); }
#line 1237 "build/parser.cpp" // lalr1.cc:847
    break;

  case 72:
#line 257 "parser.yy" // lalr1.cc:847
    {(yystack_[2].value.vect)->push_back((yystack_[0].value.nodeptr));(yylhs.value.vect)=(yystack_[2].value.vect);}
#line 1243 "build/parser.cpp" // lalr1.cc:847
    break;

  case 73:
#line 268 "parser.yy" // lalr1.cc:847
    { // Sin argumentos, devuelve un tipo ()
		(yylhs.value.nodeptr)=new NodeExprAnon(nullptr, new NamedNodeList(), new NodeProg((yystack_[1].value.vect)));
	}
#line 1251 "build/parser.cpp" // lalr1.cc:847
    break;

  case 74:
#line 271 "parser.yy" // lalr1.cc:847
    { // devuelve ()
	    (yylhs.value.nodeptr)=new NodeExprAnon(nullptr, (yystack_[4].value.vectnom), new NodeProg((yystack_[1].value.vect)));
	}
#line 1259 "build/parser.cpp" // lalr1.cc:847
    break;

  case 75:
#line 274 "parser.yy" // lalr1.cc:847
    { 
		(yylhs.value.nodeptr)=new NodeExprAnon((NodeType *) (yystack_[6].value.nodeptr), (yystack_[4].value.vectnom), new NodeProg((yystack_[1].value.vect)));
	}
#line 1267 "build/parser.cpp" // lalr1.cc:847
    break;

  case 76:
#line 277 "parser.yy" // lalr1.cc:847
    { //Obligatorio resaltar el () porque si no, es ambiguo.
		(yylhs.value.nodeptr)=new NodeExprAnon((NodeType *) (yystack_[5].value.nodeptr), new NamedNodeList(), new NodeProg((yystack_[1].value.vect)));
	}
#line 1275 "build/parser.cpp" // lalr1.cc:847
    break;

  case 77:
#line 284 "parser.yy" // lalr1.cc:847
    {
		auto aux=new NodeDecl((NodeType *)(yystack_[2].value.nodeptr), *(yystack_[0].value.stringval), nullptr);
		(yylhs.value.nodeptr)=aux;
	}
#line 1284 "build/parser.cpp" // lalr1.cc:847
    break;

  case 78:
#line 288 "parser.yy" // lalr1.cc:847
    {
		auto aux=new NodeDecl((NodeType *)(yystack_[4].value.nodeptr), *(yystack_[2].value.stringval),(NodeExpr *)(yystack_[0].value.nodeptr));
		(yylhs.value.nodeptr)=aux;
	}
#line 1293 "build/parser.cpp" // lalr1.cc:847
    break;

  case 79:
#line 292 "parser.yy" // lalr1.cc:847
    {
		((NodeDecl *) (yystack_[2].value.nodeptr))->addargs(nullptr,*(yystack_[0].value.stringval));
		(yylhs.value.nodeptr)=(yystack_[2].value.nodeptr);
	}
#line 1302 "build/parser.cpp" // lalr1.cc:847
    break;

  case 80:
#line 296 "parser.yy" // lalr1.cc:847
    {
		((NodeDecl *) (yystack_[4].value.nodeptr))->addargs((NodeExpr *)(yystack_[0].value.nodeptr),*(yystack_[2].value.stringval));
		(yylhs.value.nodeptr)=(yystack_[4].value.nodeptr);
	}
#line 1311 "build/parser.cpp" // lalr1.cc:847
    break;

  case 81:
#line 303 "parser.yy" // lalr1.cc:847
    { //Array con tamaño a determinar
		(yylhs.value.nodeptr)=new NodeTypeArr((NodeType *) (yystack_[2].value.nodeptr));
	}
#line 1319 "build/parser.cpp" // lalr1.cc:847
    break;

  case 82:
#line 306 "parser.yy" // lalr1.cc:847
    { //tupla anónima
		(yylhs.value.nodeptr)=new NodeTypeTuple((yystack_[1].value.vect));
	}
#line 1327 "build/parser.cpp" // lalr1.cc:847
    break;

  case 83:
#line 309 "parser.yy" // lalr1.cc:847
    { //tupla anónima vacía
		(yylhs.value.nodeptr)=new NodeTypeTuple(new vector<Node *>);
	}
#line 1335 "build/parser.cpp" // lalr1.cc:847
    break;

  case 84:
#line 312 "parser.yy" // lalr1.cc:847
    { //tipo función
		(yylhs.value.nodeptr)=new NodeTypeFunc((NodeType *)(yystack_[3].value.nodeptr), (yystack_[1].value.vect));
	}
#line 1343 "build/parser.cpp" // lalr1.cc:847
    break;

  case 85:
#line 315 "parser.yy" // lalr1.cc:847
    { //tipo función
		(yylhs.value.nodeptr)=new NodeTypeFunc((NodeType *)(yystack_[2].value.nodeptr), new vector<Node *>);
	}
#line 1351 "build/parser.cpp" // lalr1.cc:847
    break;

  case 86:
#line 318 "parser.yy" // lalr1.cc:847
    { //tupla con nombres
		(yylhs.value.nodeptr)=new NodeTypeNamedTuple((yystack_[1].value.vectnom));
	}
#line 1359 "build/parser.cpp" // lalr1.cc:847
    break;

  case 87:
#line 321 "parser.yy" // lalr1.cc:847
    {(yylhs.value.nodeptr)=new NodeTypeInt;}
#line 1365 "build/parser.cpp" // lalr1.cc:847
    break;

  case 88:
#line 325 "parser.yy" // lalr1.cc:847
    {
		auto aux=new vector<Node *>;
		aux->push_back((NodeType *) (yystack_[0].value.nodeptr));
		(yylhs.value.vect)=aux;
	}
#line 1375 "build/parser.cpp" // lalr1.cc:847
    break;

  case 89:
#line 330 "parser.yy" // lalr1.cc:847
    {(yystack_[2].value.vect)->push_back((Node *)(yystack_[0].value.nodeptr)); (yylhs.value.vect)=(yystack_[2].value.vect);}
#line 1381 "build/parser.cpp" // lalr1.cc:847
    break;

  case 90:
#line 334 "parser.yy" // lalr1.cc:847
    {
		NamedNodeList* aux=new NamedNodeList;
		aux->push_back(make_pair((NodeType *)(yystack_[2].value.nodeptr), *(yystack_[0].value.stringval)));
		(yylhs.value.vectnom)=aux;
	}
#line 1391 "build/parser.cpp" // lalr1.cc:847
    break;

  case 91:
#line 339 "parser.yy" // lalr1.cc:847
    {
		auto aux=(yystack_[4].value.vectnom);
		aux->push_back(make_pair((NodeType *)(yystack_[2].value.nodeptr),*(yystack_[0].value.stringval)));
		(yylhs.value.vectnom)=aux;
	}
#line 1401 "build/parser.cpp" // lalr1.cc:847
    break;

  case 92:
#line 348 "parser.yy" // lalr1.cc:847
    {
		(yylhs.value.nodeptr)=new NodeDeffun((NodeType*)(yystack_[4].value.nodeptr), *(yystack_[3].value.stringval), new NamedNodeList(), new NodeProg((yystack_[1].value.vect)));
	}
#line 1409 "build/parser.cpp" // lalr1.cc:847
    break;

  case 93:
#line 351 "parser.yy" // lalr1.cc:847
    {
		(yylhs.value.nodeptr)=new NodeDeffun((NodeType*)(yystack_[7].value.nodeptr), *(yystack_[6].value.stringval), (yystack_[4].value.vectnom), new NodeProg((yystack_[1].value.vect)));
	}
#line 1417 "build/parser.cpp" // lalr1.cc:847
    break;

  case 94:
#line 354 "parser.yy" // lalr1.cc:847
    {
		(yylhs.value.nodeptr)=new NodeDeffun((NodeType*)(yystack_[6].value.nodeptr), *(yystack_[5].value.stringval), new NamedNodeList, new NodeProg((yystack_[1].value.vect)));
	}
#line 1425 "build/parser.cpp" // lalr1.cc:847
    break;


#line 1429 "build/parser.cpp" // lalr1.cc:847
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -87;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
     394,   -87,   -87,   -87,   394,   394,   394,   394,   394,   394,
     394,   394,   394,    25,   394,     7,   394,   -87,     9,   102,
     142,   155,    15,    -3,    -1,    14,    21,   181,    98,   185,
     173,   157,   -87,    35,   -87,   187,    34,   -87,   -87,    96,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,    26,
      92,     6,    62,   179,   -87,   -87,   -87,   394,   394,   394,
      -4,   394,    -4,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   -87,   -87,   394,   394,    49,   -87,    73,   -17,
      97,    28,   353,   -87,   109,     2,   -87,     2,    90,   -87,
     -87,   -87,   -87,    44,   -87,    99,   -87,   -87,    -3,   -87,
      83,    -1,    14,    21,   181,    98,    98,   185,   185,   185,
     185,   173,   173,   157,   157,   -87,   -87,   -87,   -87,    74,
      75,   -87,   103,    46,   394,   121,    44,   106,   104,    76,
      78,   -87,   123,   -87,   112,   105,   394,   128,   394,   394,
     -87,   -87,   394,   110,   104,    79,   191,   394,    82,   394,
      65,   -87,   129,   -87,   143,   233,   -87,   -87,   -87,   -87,
     394,   137,   -87,   -87,   -87,   245,   -87,   112,   394,   -87,
     -87,   287,   394,   -87,   299,   -87,   341,   -87,   -87
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,    68,    65,    87,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     4,     0,    10,
      15,    16,    21,    23,    25,    27,    29,    31,    34,    39,
      42,    45,    49,    59,    66,     0,     0,     7,    50,     0,
      51,    53,    52,    54,    55,    56,    57,    58,    83,     0,
      88,     0,     0,     0,     1,     3,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    60,    61,    70,     0,     0,     6,     0,     0,
       0,     0,     0,    69,     0,     0,    82,     0,    86,    73,
       8,     9,    11,     0,    13,     0,    12,    14,    22,    17,
      19,    24,    26,    28,    30,    32,    33,    36,    35,    37,
      38,    40,    41,    43,    44,    46,    47,    48,    71,     0,
       0,    64,    79,     0,     0,    77,     0,    85,    88,     0,
       0,    81,     0,    90,    89,     0,     0,     0,     0,     0,
      62,    63,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    84,     0,    67,     0,     0,    18,    20,    72,    80,
       0,     0,    92,    78,    86,     0,    85,    88,     0,    91,
      74,     0,     0,    76,     0,    94,     0,    75,    93
  };

  const short int
  Parser::yypgoto_[] =
  {
     -87,   -87,    -6,   -13,    -9,   -50,   -63,   -62,   -87,   125,
     133,   134,   149,   170,   141,    42,   139,   158,    13,   -87,
     -87,   101,   -87,     0,   -86,   -81,   -87
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
     129,    34,    35,    39,    51,    52,    37
  };

  const unsigned char
  Parser::yytable_[] =
  {
      36,   109,   110,    55,    49,   139,     3,    54,    53,   102,
     140,   106,     3,    50,    36,    65,    36,    38,    40,    41,
      42,    43,    44,    45,    46,    47,   133,    66,    95,     1,
      56,   134,    63,     2,   128,     3,     4,     5,     3,   103,
      55,    64,    89,    67,    14,   136,    82,    83,   100,   101,
      96,    68,   155,    36,     3,   158,     3,   131,     6,     7,
     105,    90,   105,     8,     9,    10,    11,    12,    13,    48,
      93,   136,   137,    14,   139,     3,   130,    91,    84,    92,
      85,   132,    86,   142,    97,   166,   167,   136,    48,   136,
     153,   138,   125,   126,   127,   144,   149,   145,    95,   168,
      97,    97,   169,   138,    97,   135,    98,   173,   136,   176,
     148,    71,    72,   117,   118,   119,   120,   143,   150,    94,
     161,   151,   162,   171,    57,    58,   174,   152,   156,    73,
      74,    94,   164,   154,    36,    91,   138,    92,   146,    91,
     165,    92,    91,    55,   147,   157,    36,   160,   160,   147,
     147,   179,    55,   175,   159,   160,    36,   147,   170,    36,
     177,   104,    55,   107,   181,    36,    59,    60,    55,   163,
      36,    55,   184,    55,   141,    36,   186,   178,    36,    61,
      62,    36,    36,     1,    36,   182,    36,     2,   108,     3,
       4,     5,    79,    80,    81,     1,    69,    70,   111,     2,
     112,     3,     4,     5,    75,    76,    77,    78,    87,    88,
     115,   116,     6,     7,   121,   122,   113,     8,     9,    10,
      11,    12,    13,     0,     6,     7,     0,    14,    99,     8,
       9,    10,    11,    12,    13,   123,   124,     1,   114,    14,
     172,     2,     0,     3,     4,     5,     0,     0,     0,     1,
       0,     0,     0,     2,     0,     3,     4,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     7,     0,     0,
       0,     8,     9,    10,    11,    12,    13,     0,     6,     7,
       0,    14,   180,     8,     9,    10,    11,    12,    13,     0,
       0,     1,     0,    14,   183,     2,     0,     3,     4,     5,
       0,     0,     0,     1,     0,     0,     0,     2,     0,     3,
       4,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     7,     0,     0,     0,     8,     9,    10,    11,    12,
      13,     0,     6,     7,     0,    14,   185,     8,     9,    10,
      11,    12,    13,     0,     0,     1,     0,    14,   187,     2,
       0,     3,     4,     5,     0,     0,     0,     1,     0,     0,
       0,     2,     0,     3,     4,     5,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     7,     0,     0,     0,     8,
       9,    10,    11,    12,    13,     0,     6,     7,     0,    14,
     188,     8,     9,    10,    11,    12,    13,     0,     1,   141,
       0,    14,     2,     0,     3,     4,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,     7,     0,
       0,     0,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,    14
  };

  const short int
  Parser::yycheck_[] =
  {
       0,    64,    64,    16,    13,    91,    10,     0,    14,    59,
      91,    61,    10,    13,    14,    18,    16,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    43,    28,    22,     4,
      21,    48,    17,     8,    84,    10,    11,    12,    10,    43,
      53,    26,     8,    29,    48,    43,    11,    12,    57,    58,
      44,    30,   133,    53,    10,   136,    10,     8,    33,    34,
      60,    27,    62,    38,    39,    40,    41,    42,    43,    44,
      44,    43,    44,    48,   160,    10,    85,    43,    43,    45,
      45,     8,    47,    92,    22,   148,   148,    43,    44,    43,
      44,    91,    79,    80,    81,    95,    22,    97,    22,   149,
      22,    22,   152,   103,    22,     8,    44,   157,    43,    44,
      27,    13,    14,    71,    72,    73,    74,     8,    44,    27,
      44,    46,    44,    44,    22,    23,    44,    24,   134,    31,
      32,    27,    27,   133,   134,    43,   136,    45,    48,    43,
     146,    45,    43,   156,    45,    24,   146,    43,    43,    45,
      45,     8,   165,   159,    48,    43,   156,    45,    48,   159,
     160,    60,   175,    62,   170,   165,    24,    25,   181,    46,
     170,   184,   178,   186,    46,   175,   182,    48,   178,    24,
      25,   181,   182,     4,   184,    48,   186,     8,    63,    10,
      11,    12,    35,    36,    37,     4,    15,    16,    65,     8,
      66,    10,    11,    12,    19,    20,    33,    34,    21,    22,
      69,    70,    33,    34,    75,    76,    67,    38,    39,    40,
      41,    42,    43,    -1,    33,    34,    -1,    48,    49,    38,
      39,    40,    41,    42,    43,    77,    78,     4,    68,    48,
      49,     8,    -1,    10,    11,    12,    -1,    -1,    -1,     4,
      -1,    -1,    -1,     8,    -1,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    -1,    33,    34,
      -1,    48,    49,    38,    39,    40,    41,    42,    43,    -1,
      -1,     4,    -1,    48,    49,     8,    -1,    10,    11,    12,
      -1,    -1,    -1,     4,    -1,    -1,    -1,     8,    -1,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    -1,    33,    34,    -1,    48,    49,    38,    39,    40,
      41,    42,    43,    -1,    -1,     4,    -1,    48,    49,     8,
      -1,    10,    11,    12,    -1,    -1,    -1,     4,    -1,    -1,
      -1,     8,    -1,    10,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    -1,    33,    34,    -1,    48,
      49,    38,    39,    40,    41,    42,    43,    -1,     4,    46,
      -1,    48,     8,    -1,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    -1,    -1,
      -1,    -1,    48
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     4,     8,    10,    11,    12,    33,    34,    38,    39,
      40,    41,    42,    43,    48,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    71,    72,    73,    76,    68,    73,
      68,    68,    68,    68,    68,    68,    68,    68,    44,    54,
      73,    74,    75,    52,     0,    53,    21,    22,    23,    24,
      25,    24,    25,    17,    26,    18,    28,    29,    30,    15,
      16,    13,    14,    31,    32,    19,    20,    33,    34,    35,
      36,    37,    11,    12,    43,    45,    47,    21,    22,     8,
      27,    43,    45,    44,    27,    22,    44,    22,    44,    49,
      54,    54,    55,    43,    71,    73,    55,    71,    59,    56,
      57,    60,    61,    62,    63,    64,    64,    65,    65,    65,
      65,    66,    66,    67,    67,    68,    68,    68,    55,    70,
      54,     8,     8,    43,    48,     8,    43,    44,    73,    74,
      75,    46,    54,     8,    73,    73,    48,    45,    27,    22,
      44,    46,    24,    44,    73,    75,    52,    24,    75,    48,
      43,    44,    44,    46,    27,    52,    56,    57,    55,    55,
      48,    44,    49,    55,    44,    52,    44,    73,    48,     8,
      49,    52,    48,    49,    52,    49,    52,    49,    49
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    50,    51,    52,    52,    53,    53,    53,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    56,    56,    56,
      57,    57,    58,    58,    59,    59,    60,    60,    61,    61,
      62,    62,    63,    63,    63,    64,    64,    64,    64,    64,
      65,    65,    65,    66,    66,    66,    67,    67,    67,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      70,    70,    70,    71,    71,    71,    71,    72,    72,    72,
      72,    73,    73,    73,    73,    73,    73,    73,    74,    74,
      75,    75,    76,    76,    76
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     2,     2,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     1,     3,     5,     3,
       5,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     1,
       2,     2,     4,     4,     3,     1,     1,     4,     1,     3,
       0,     1,     3,     3,     6,     7,     6,     3,     5,     3,
       5,     3,     3,     2,     4,     3,     3,     1,     1,     3,
       3,     5,     5,     8,     7
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"end of line\"",
  "\"integer\"", "\"float\"", "\"string\"", "\"bool\"", "\"identifier\"",
  "\"type identifier\"", "INT", "MASMAS", "MENOSMENOS", "MAYORIGUAL",
  "MENORIGUAL", "IGUALIGUAL", "NOIGUAL", "BARRABARRA", "ANDAND",
  "MENORMENOR", "MAYORMAYOR", "';'", "','", "'\\''", "'='", "'@'", "'?'",
  "':'", "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'!'", "'~'", "'r'", "'c'", "'b'", "'('", "')'", "'['", "']'",
  "'.'", "'{'", "'}'", "$accept", "program", "stmt_list", "stmt", "expr15",
  "expr14", "expr14_1", "expr14_2", "expr13", "expr12", "expr11", "expr10",
  "expr9", "expr8", "expr7", "expr6", "expr5", "expr4", "expr3", "expr1",
  "lista_args", "funcion_anonima", "declaracion", "type", "lista_types",
  "lista_types_nombre", "def_funcion_cte", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,    82,    82,    87,    90,    98,    99,   100,   108,   109,
     110,   122,   123,   124,   125,   126,   127,   135,   136,   143,
     147,   154,   159,   160,   164,   165,   169,   170,   174,   175,
     179,   180,   184,   185,   186,   190,   191,   192,   193,   194,
     198,   199,   200,   204,   205,   206,   210,   211,   212,   213,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     234,   235,   236,   241,   244,   245,   246,   247,   250,   251,
     255,   256,   257,   268,   271,   274,   277,   284,   288,   292,
     296,   303,   306,   309,   312,   315,   318,   321,   325,   330,
     334,   339,   348,   351,   354
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,     2,     2,    37,    30,    23,
      43,    44,    35,    33,    22,    34,    47,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    27,    21,
      31,    24,    32,    26,    25,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,    29,     2,     2,     2,    42,    41,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,    48,    28,    49,    39,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20
    };
    const unsigned int user_token_number_max_ = 275;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 20 "parser.yy" // lalr1.cc:1155
} // parser
#line 2023 "build/parser.cpp" // lalr1.cc:1155
#line 362 "parser.yy" // lalr1.cc:1156


void parser::Parser::error(const Parser::location_type& l, const std::string& m){
    driver.error(l,m);
}
