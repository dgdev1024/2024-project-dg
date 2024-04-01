/** @file DG/Core/StreamFormat.hpp */

#pragma once

#include <DG/Common.hpp>

namespace dg
{

  /**
   * @brief   Writes a formatted string into the given output stream. This
   *          overload function is called if no variadic template arguments are
   *          provided.
   * 
   * @param   output_stream   A handle to the output stream to write to.
   * @param   format          The string to be formatted and written.
   */
  inline void streamFormat (
    std::ostream& output_stream,
    const Char*   format
  )
  {
    output_stream << format;
  }

  /**
   * @brief   Writes a formatted string into the given output stream.
   * 
   * @tparam FirstArg         The type of the first variadic argument provided.
   * @tparam ...RemainingArgs The types of the remaining variadic arguments.
   * 
   * @param output_stream     A handle to the output stream to write to.
   * @param format            The string to be formatted.
   * @param first_arg         The argument to fill the first placeholder with.
   * @param ...remaining_args The remaining variadic arguments.
   */
  template <typename FirstArg, typename... RemainingArgs>
  inline void streamFormat (
    std::ostream&     output_stream,
    const Char*       format,
    FirstArg          first_arg,
    RemainingArgs...  remaining_args
  )
  {

    // Iterate through the string until the null terminator ('\0') is found.
    for (; *format != '\0'; ++format)
    {

      if (*format == '{' && *(format + 1) == '}')
      {
        output_stream << first_arg;
        streamFormat(output_stream, format + 2, remaining_args...);
        return;
      }

      output_stream << *format;

    }

  }

}
