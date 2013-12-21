#include <kernel/Kernel.hpp>
// C-STL
#include <cstdio>
#include <cstdlib>
#include <cstring>
// POSIX
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace Fairy
{

Kernel::Kernel(boost::asio::io_service & io, const boost::asio::ip::tcp::endpoint & endpoint) :
	m_reg(),
	//m_mem(),
	m_io_service(io),
	m_acceptor(io, endpoint),
	m_sock(io)
{
	
}//constructor(io_service, endpoint)

}//namespace Fairy

