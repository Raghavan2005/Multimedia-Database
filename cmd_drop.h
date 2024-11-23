#pragma once
#ifndef CMD_DROP_H
#define CMD_DROP_H

#include <string>
#include <filesystem>
#include <iostream>

// Namespace alias for filesystem
namespace fs = std::filesystem;

/**
 * Deletes a folder and all its contents.
 *
 * @param path The path of the folder to delete.
 * @return True if the folder was successfully deleted, false otherwise.
 */
bool deleteFolder(const std::string& path);

/**
 * Processes the "drop" command, allowing the removal of databases or pools.
 *
 * Command Format:
 * - `drop db <dbname>`: Drops the specified database.
 * - `drop pool <poolname>`: Drops the specified pool from the active database.
 *
 * @param command The full command string to process.
 */
void process_drop_command(const std::string& command);

#endif // CMD_DROP_H
