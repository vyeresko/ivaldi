#pragma once
#include "Precompiled.h"

#include "Core.h"
#include "IvaldiApp.h"
#include "Log/Log.h"

int main(int argc, char* argv[])
{
	ivaldi::Logger::setGlobalPattern("%^[%T] %n: %v%$");
	auto logger = ivaldi::Logger::create("Ivaldi");
	logger.info("Ivaldi logger initialized");

	auto application = ivaldi::createApplication();
	application->init();
	logger.info("Application initialized");

	while (true) {
		application->update();
	}
}