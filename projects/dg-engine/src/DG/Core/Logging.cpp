/** @file DG/Core/Logging.cpp */

#include <DG/Core/Logging.hpp>

namespace dg
{

  /** Log Class ***************************************************************/

  Log::Log (
    const String&       name
  ) :
    m_name  { name },
    m_cout  { std::cout },
    m_cerr  { std::cerr }
  {
    if (m_name.empty() == true)
    {
      m_name = "Log";
    }
  }

  Log::Log (
    std::ostream&       stream,
    const String&       name
  ) :
    m_name  { name },
    m_cout  { stream },
    m_cerr  { stream }
  {
    if (m_name.empty() == true)
    {
      m_name = "Log";
    }
  }

  /** Logging Static Class ****************************************************/

  Shared<Log> Logging::s_EngineLog = nullptr;
  Shared<Log> Logging::s_ClientLog = nullptr;

  void Logging::initialize ()
  {
    s_EngineLog = std::make_shared<Log>("ENGINE");
    s_ClientLog = std::make_shared<Log>("CLIENT");
  }

  Shared<Log>& Logging::getEngineLog ()
  {
    return s_EngineLog;
  }

  Shared<Log>& Logging::getClientLog ()
  {
    return s_ClientLog;
  }

}
