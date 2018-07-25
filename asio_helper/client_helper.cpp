#include <boost/asio.hpp>
#include <memory>
#include <deque>

// 这是只是使用 asio 能使用tcp，把数据发给 gochart，非正式实现。

using boost::asio::ip::tcp;

typedef std::deque<int> chat_message_queue;

class AsioClient
{
public:
	AsioClient(boost::asio::io_context& io_context,
		const tcp::resolver::results_type& endpoints)
		: io_context_(io_context),
		socket_(io_context)
	{
		do_connect(endpoints);
	}

	void Write(const int& msg)
	{
		boost::asio::post(io_context_,
			[this, msg]()
		{
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(msg);
			if (!write_in_progress)
			{
				do_write();
			}
		});
	}

	void Close()
	{
		boost::asio::post(io_context_, [this]() { socket_.close(); });
	}

private:
	void do_connect(const tcp::resolver::results_type& endpoints)
	{
		boost::asio::async_connect(socket_, endpoints,
			[this](boost::system::error_code ec, tcp::endpoint)
		{
			if (ec)
			{
				// error
				exit(1);
			}
		});
	}

	void do_write()
	{
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			[this](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				write_msgs_.pop_front();
				if (!write_msgs_.empty())
				{
					do_write();
				}
			}
			else
			{
				socket_.close();
			}
		});
	}

private:
	boost::asio::io_context& io_context_;
	tcp::socket socket_;
	chat_message_queue write_msgs_;
};

std::shared_ptr<AsioClient> InitAsioClient(const char* ip, const char* port)
{
	static boost::asio::io_context io_context;
	tcp::resolver resolver(io_context);
	auto endpoints = resolver.resolve(ip, port);
	std::thread t([&io_context]() { io_context.run(); });
	return std::make_shared<AsioClient>(io_context, resolver);
}