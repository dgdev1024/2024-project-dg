/** @file DG/Core/Logging.hpp */

#pragma once

#include <DG/Core/StreamFormat.hpp>

namespace dg
{

  /**
   * @brief   The @a `Log` class provides a means of logging categorized outputs
   *          to given output streams.
   */
  class Log
  {
  public:

    /**
     * @brief   Constructs a @a `Log` using the given string name.
     * 
     * @param   name  The name of the new @a `Log`. 
     */
    Log (
      const String&       name = ""
    );

    /**
     * @brief   Constructs a @a `Log` using the given string name, and the given
     *          output stream for both standard and error logging.
     * 
     * @param   stream  A handle to the output stream used for standard and for
     *                  error logging.
     * @param   name    The name of the new @a `Log`.
     */
    Log (
      std::ostream&       stream,
      const String&       name    = ""
    );

    /**
     * @brief   Writes an information string to the @a `Log`'s standard output.
     * 
     * @tparam  ...Args   The types of the given variadic arguments.
     * 
     * @param   format    The string to be formatted.
     * @param   ...args   The variadic arguments to format the string with.
     */
    template <typename... Args>
    inline void info (
      const Char* format,
      Args... args
    )
    {
      streamFormat(m_cout, "[{} | Info] ", m_name);
      streamFormat(m_cout, format, args...);
      m_cout << "\n";
    }

    /**
     * @brief   Writes a warning string to the @a `Log`'s error output.
     * 
     * @tparam  ...Args   The types of the given variadic arguments.
     * 
     * @param   format    The string to be formatted.
     * @param   ...args   The variadic arguments to format the string with.
     */
    template <typename... Args>
    inline void warning (
      const Char* format,
      Args... args
    )
    {
      streamFormat(m_cerr, "[{} | Warning] ", m_name);
      streamFormat(m_cerr, format, args...);
      m_cerr << std::endl;
    }

    /**
     * @brief   Writes an error string to the @a `Log`'s error output.
     * 
     * @tparam  ...Args   The types of the given variadic arguments.
     * 
     * @param   format    The string to be formatted.
     * @param   ...args   The variadic arguments to format the string with.
     */
    template <typename... Args>
    inline void error (
      const Char* format,
      Args... args
    )
    {
      streamFormat(m_cerr, "[{} | Error] ", m_name);
      streamFormat(m_cerr, format, args...);
      m_cerr << std::endl;
    }

    /**
     * @brief   Writes a critical error string to the @a `Log`'s error output.
     *          This should only be used when throwing exceptions.
     * 
     * @tparam  ...Args   The types of the given variadic arguments.
     * 
     * @param   format    The string to be formatted.
     * @param   ...args   The variadic arguments to format the string with.
     */
    template <typename... Args>
    inline void critical (
      const Char* format,
      Args... args
    )
    {
      streamFormat(m_cerr, "[{} | Critical!] ", m_name);
      streamFormat(m_cerr, format, args...);
      m_cerr << std::endl;
    }

  private:

    /**
     * @brief The name, if any, of this @a `Log`.
     */
    String m_name = "";

    /**
     * @brief A handle to the output stream used for standard output.
     */
    std::ostream& m_cout;

    /**
     * @brief A handle to the output stream used for error output.
     */
    std::ostream& m_cerr;

  };

  /**
   * @brief   The @a `Logging` class is a static helper class used for logging
   *          to the console.
   */
  class Logging
  {
  public:

    /**
     * @brief   Initializes the internal loggers.
     */
    static void initialize ();

    /**
     * @brief   Retrieves the engine's logger.
     * 
     * @return  A pointer to the engine's logger.
     */
    static Shared<Log>& getEngineLog ();

    /**
     * @brief   Retrieves the client's logger. 
     * 
     * @return  A pointer to the client's logger.
     */
    static Shared<Log>& getClientLog ();

  private:

    /**
     * @brief   A pointer to the engine's logger.
     */
    static Shared<Log> s_EngineLog;

    /**
     * @brief   A pointer to the client's logger.
     */
    static Shared<Log> s_ClientLog;

  };

}

#define DG_ENGINE_INFO(...)  ::dg::Logging::getEngineLog()->info(__VA_ARGS__)
#define DG_ENGINE_WARN(...)  ::dg::Logging::getEngineLog()->warning(__VA_ARGS__)
#define DG_ENGINE_ERROR(...) ::dg::Logging::getEngineLog()->error(__VA_ARGS__)
#define DG_ENGINE_CRIT(...)  ::dg::Logging::getEngineLog()->critical(__VA_ARGS__)

#define DG_ENGINE_THROW(except, ...) \
  DG_ENGINE_CRIT(__VA_ARGS__); \
  throw except { #except }

#define DG_INFO(...)         ::dg::Logging::getClientLog()->info(__VA_ARGS__)
#define DG_WARN(...)         ::dg::Logging::getClientLog()->warning(__VA_ARGS__)
#define DG_ERROR(...)        ::dg::Logging::getClientLog()->error(__VA_ARGS__)
#define DG_CRIT(...)         ::dg::Logging::getClientLog()->critical(__VA_ARGS__)

#define DG_THROW(except, ...) \
  DG_CRIT(__VA_ARGS__); \
  throw except { #except }
