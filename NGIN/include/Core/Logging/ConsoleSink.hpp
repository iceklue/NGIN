#pragma once
#include "LogSink.hpp"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>  // for isatty()
#endif

namespace NGIN
{
	/**
	 * @class ConsoleSink
	 * @brief A log sink that prints log messages to the standard output or error.
	 *
	 * Logs messages to the standard output or error based on their severity level,
	 * and sets the output color based on the severity level.
	 */
	class NGIN_API ConsoleSink : public LogSink
	{
	public:
		ConsoleSink();

		/**
		 * @brief Logs a message to the standard output or error.
		 *
		 * @param level The severity level of the message.
		 * @param message The message to be logged.
		 */
		virtual void Log(LogLevel level, const std::string& message) override;

		virtual void Flush() override;

	private:
#ifdef _WIN32
		HANDLE hConsole;
#else
		bool isTerminal;
#endif

		/**
		 * @brief Sets the output color based on the severity level.
		 *
		 * @param level The severity level of the message.
		 */
		void SetColor(LogLevel level);

		/**
		 * @brief Resets the output color to default.
		 */
		void ResetColor();
	};

} // namespace NGIN