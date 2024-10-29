#ifndef __ENGINE_H__
#define __ENGINE_H__
#pragma once

#include <vector>

#include "Log.h"

class MyWindow;
class Input;
class Renderer;

class Engine
{
public:
	static Engine& Instance() {
		static Engine instance;  // La instancia única de la clase Engine
		return instance;
	}

	void Awake();
	void Start();

	bool PreUpdate();
	void Update(double dt);

	void CleanUp();

	std::vector<LogInfo> GetLogs();
	void AddLog(LogType type, const char* entry);
	void CleanLogs();

	// Evita la copia y asignación del singleton
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

public:

	double dt = 0;
	bool vsync = false;

	MyWindow* window = nullptr;
	Input* input = nullptr;
	Renderer* renderer = nullptr;

private:
	// Constructor y destructor privados para el singleton
	Engine() = default;
	~Engine();
	// Logs
	LogInfo logInfo;
	std::vector<LogInfo> logs;
};

#endif // !__ENGINE_H__