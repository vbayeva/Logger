#pragma once

#include <string>
#include <mutex>
#include <fstream>

#include "LogLevel.hpp"

/**
* @class Logger
* @brief Singleton class providing a thread - safe logging mechanism.
*
* The Logger class allows logging messages with different severity levels
* to both the console and a file.It ensures that log messages from multiple
* threads are not interleaved or corrupted by using mutex locks.
*/
class Logger
{
public:
	/**
	 * @brief Retrieves the singleton instance of the Logger class.
	 *
	 * @return Reference to the Logger instance.
	 *
	 * This method ensures that only one instance of the Logger exists
	 * throughout the application. It is thread-safe and creates the
	 * instance upon the first call.
	 */
	static Logger& getInstance();

	/**
	 * @brief Logs a message with the specified severity level.
	 *
	 * @param level   The severity level of the log message.
	 * @param message The message string to log.
	 *
	 * This method is thread-safe and ensures that log messages from
	 * multiple threads are written atomically. It writes the formatted
	 * message to the console and, if a log file is set, to the file.
	 */
	void log(LogLevel level, const std::string& message);
	/**
	 * @brief Sets the log file where messages will be written.
	 *
	 * @param filename The name or path of the log file.
	 *
	 * This method opens the specified file in append mode. If the file
	 * cannot be opened, it outputs an error message to std::cerr.
	 * It should be called before any logging occurs to ensure that
	 * messages are written to the correct file.
	 */
	void setLogFile(const std::string& finename);

private:
	/**
	 * @brief Private constructor to enforce singleton pattern.
	 *
	 * The constructor is private to prevent direct instantiation.
	 */
	Logger() {};
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	std::mutex log_mutex;
	std::ofstream log_file;

	/**
	 * @brief Retrieves the current system time as a formatted string.
	 *
	 * @return String representing the current time in "YYYY-MM-DD HH:MM:SS" format.
	 *
	 * This method is used internally to timestamp log messages.
	 */
	std::string getCurrentTime();
};