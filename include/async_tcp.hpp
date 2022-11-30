#ifndef _ASYNC_TCP
#define _ASYNC_TCP
// Standard library imports
#include <string>
#include <iostream>
#include <memory>
// Boost imports
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

// This server class Servers accepts incoming connections
class TCP_connection
  : public boost::enable_shared_from_this<TCP_connection>
{
    public:
        static boost::shared_ptr<TCP_connection> create(boost::asio::io_context& io_context);
        boost::asio::ip::tcp::socket& socket();
        void start_listening();
    private:
        TCP_connection(boost::asio::io_context& io_context);
        void handle_read(const boost::system::error_code error,size_t bytesrecieved );
        boost::asio::ip::tcp::socket _socket;
        std::array<char,1<<15> _message; 
};

class Async_TCP_server
{
    public:
        Async_TCP_server()=delete;
        Async_TCP_server(int PortNum);
    private:
        void start_accept();
        void handle_accept(boost::shared_ptr<TCP_connection> connection_request,
            const boost::system::error_code& error);
        boost::asio::io_context io_context_;
        boost::asio::ip::tcp::acceptor _acceptor;
};

class Async_TCP_client
{
    public:
        Async_TCP_client()=delete;
        Async_TCP_client(std::string serverIP,int PortNum);
    private:
        void sendPacket(std::shared_ptr<char *> buffer, std::size_t sizeofBuffer);
        void recievePacket();
};

#endif //_ASYNC_TCP