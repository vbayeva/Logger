#include "Logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

Logger& Logger::getInstance() {
	static Logger instance;
	return instance;
}

void Logger::log(LogLevel level, const std::string& message) {
	std::lock_guard<std::mutex> lock(log_mutex);

	std::string message_level;

	switch (level) {
		case LogLevel::INFO:
			message_level = "INFO";
			break;
		case LogLevel::WARNING:
			message_level = "WARNING";
			break;
		case LogLevel::ERROR:
			message_level = "ERROR";
			break;
		case LogLevel::DEBUG:
			message_level = "DEBUG";
			break;
		default:
			break;
	}

	std::string timestamp = getCurrentTime();

	std::string log_message = "[" + timestamp + "] [" + message_level + "] " + message;
	std::cout << log_message << std::endl;

	if (log_file.is_open()) {
		log_file << log_message << std::endl;
	}
}

void Logger::setLogFile(const std::string& filename) {
	std::lock_guard<std::mutex> lock(log_mutex);
	log_file.open(filename, std::ios_base::app);

	if (!log_file.is_open()) {
		std::cerr << "Unable to open log file: " << filename << std::endl;
	}
}

std::string Logger::getCurrentTime() {
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::tm buf;
#ifdef _WIN32
	localtime_s(&buf, &in_time_t);
#else
	localtime_r(&in_time_t, &buf);
#endif

	std::ostringstream ss;
	ss << std::put_time(&buf, "%Y-%m-%d %X");
	return ss.str();
}
