/** @file DG/Core/Logging.cpp */

#include <DG/Core/Logging.hpp>

namespace dg
{

  /** Log Class ***************************************************************/

  Log::Log (
    const std::string&  name
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
    const std::string&  name
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

  std::shared_ptr<Log> Logging::s_EngineLog = nullptr;
  std::shared_ptr<Log> Logging::s_ClientLog = nullptr;

  void Logging::initialize ()
  {
    s_EngineLog = std::make_shared<Log>();
    s_ClientLog = std::make_shared<Log>();
  }

  std::shared_ptr<Log>& Logging::getEngineLog ()
  {
    return s_EngineLog;
  }

  std::shared_ptr<Log>& Logging::getClientLog ()
  {
    return s_ClientLog;
  }

}
