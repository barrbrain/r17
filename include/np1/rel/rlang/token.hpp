// Copyright 2012 Matthew Nourse and n plus 1 computing pty limited unless otherwise noted.
// Please see LICENSE file for details.
#ifndef NP1_REL_RLANG_TOKEN_HPP
#define NP1_REL_RLANG_TOKEN_HPP


#include "np1/str.hpp"


// Special asserts that print out information available in the token.
#define NP1_TOKEN_ASSERT(cond__, tok__, message__) \
NP1_ASSERT((cond__), "line " + str::to_dec_str((tok__).line_number()) + ": " + std::string(message__) + "  token: '" + std::string((tok__).text()) + "'")

#define NP1_TOKEN_ASSERT_NO_TOKEN_TEXT(cond__, tok__, message__) \
NP1_ASSERT((cond__), "line " + str::to_dec_str((tok__).line_number()) + ": " + std::string(message__))


namespace np1 {
namespace rel {
namespace rlang {

/// An input token.
class token {
public:
  enum { MAX_TOKEN_LENGTH = 1024 };  

  typedef enum {
    TYPE_UNKNOWN = -1,
    TYPE_STRING,
    TYPE_IDENTIFIER_VARIABLE,
    TYPE_IDENTIFIER_FUNCTION,  // Never set by reader, used upstream.
    TYPE_INT,
    TYPE_UINT,
    TYPE_DOUBLE,
    TYPE_BOOL_TRUE,
    TYPE_BOOL_FALSE,
    TYPE_OPEN_PAREN,
    TYPE_CLOSE_PAREN,
    TYPE_COMMA,
    TYPE_SEMICOLON,
    TYPE_OPERATOR,
  } type_type;

public:
  token() : m_line_number(0), m_type(TYPE_UNKNOWN), m_first_matching_sym_op_fn_id(-1) {
    m_text[0] = '\0';
  }

  token(const char *text, type_type type) : m_line_number(0), m_type(type), m_first_matching_sym_op_fn_id(-1) {
    size_t text_length = strlen(text);
    NP1_ASSERT(text_length <= MAX_TOKEN_LENGTH, "Text '" + std::string(text) + "' is too long to be a token");
    memcpy(m_text, text, text_length);
    m_text[text_length] = '\0';
  }

  void assert(bool condition, const char *message) const {
    NP1_TOKEN_ASSERT(condition, *this, message);
  }

  /// Get and set stuff.  
  size_t line_number() const { return m_line_number; }
  void line_number(size_t line_number) { m_line_number = line_number; }

  type_type type() const { return m_type; }
  void type(type_type type) { m_type = type; }

  int first_matching_sym_op_fn_id() const { return m_first_matching_sym_op_fn_id; }
  void first_matching_sym_op_fn_id(size_t first_matching_sym_op_fn_id) {
    m_first_matching_sym_op_fn_id = first_matching_sym_op_fn_id;
  }

  bool is_minus() const { return (('-' == m_text[0]) && ('\0' == m_text[1])); }

  const char *text() const { return m_text; }
  char *text() { return m_text; }

  size_t max_text_length() const { return sizeof(m_text) - 1; }

private:
  size_t m_line_number;
  type_type m_type;
  int m_first_matching_sym_op_fn_id;
  char m_text[MAX_TOKEN_LENGTH + 1];
};

} // namespaces
}
}


#endif
