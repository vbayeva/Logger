#pragma once

/**
 * @enum LogLevel
 * @brief Enumeration of log severity levels.
 */
enum class LogLevel {
	INFO, /**< Informational messages */
	WARNING, /**< Warning messages indicating potential issues */
	ERROR, /**< Error messages indicating failures */
	DEBUG /**< Debug messages for debug purposes*/
};