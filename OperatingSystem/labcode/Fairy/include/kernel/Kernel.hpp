#pragma once
// STL
#include <string>
#include <stdexcept>
#include <memory>
// C-STL
#include <cstdlib>
// Boost
#include <boost/asio.hpp>
// Fairy
#include <config.hpp>
#include <hardware/Register.hpp>

namespace Fairy
{

class Kernel : public std::enable_shared_from_this<Kernel> {
public://functions
	Kernel(boost::asio::io_service & io, const boost::asio::ip::tcp::endpoint & endpoint);

	Kernel(const Kernel & rhs) = delete;
	Kernel(Kernel && rhs) = delete;
	Kernel & operator=(const Kernel & rhs) = delete;
	Kernel & operator=(Kernel && rhs) = delete;

	void
	start();

	int
	loop();

private://functions

private://members
	// Hardwares
	Register m_reg;
	//Memory m_mem;
	// asio
	boost::asio::io_service & m_io_service;
	boost::asio::ip::tcp::acceptor m_acceptor;
	boost::asio::ip::tcp::socket m_sock;
};//class Kernel

}//namespace Fairy

