#include <filesystem>

#include "common.hpp"

using namespace std;

struct File {
  std::string name;
  int         size;
};
struct Directory {
  std::vector<File>                  files;
  std::vector<std::filesystem::path> dirs;
  int                                getFileSize() {
    int sum = 0;
    for (auto& file : files) sum += file.size;
    return sum;
  }
  int totalSize = 0;
};

int main() {
  ifstream in("day_2022_07");

  std::map<std::filesystem::path, Directory> dirs;
  dirs["/"] = Directory{};

  std::filesystem::path currentDir = "/";

  std::string command;
  while (in >> command) {
    if (command == "$") {
      in >> command;
      if (command == "cd") {  // cd
        std::string dir;
        in >> dir;
        if (dir == "/")
          currentDir = "/";
        else if (dir == "..")
          currentDir = currentDir.parent_path();
        else
          currentDir /= dir;
      } else {  // ls
        // cerr << "ls in dir: " << currentDir << endl;
      }
    } else {
      if (command == "dir") {  // dir
        std::string dir;
        in >> dir;
        dirs[currentDir].dirs.push_back(dir);
      } else {  // file
        int         filesize = std::stoi(command);
        std::string filename;
        in >> filename;
        dirs[currentDir].files.push_back(File{filename, filesize});
      }
    }
  }

  std::queue<std::filesystem::path> paths;
  paths.push("/");
  while (!paths.empty()) {
    auto path = paths.front();
    paths.pop();
    for (auto& dir : dirs[path].dirs) {
      paths.push(path / dir);
    }
    int size = dirs[path].getFileSize();
    while (path != "/") {
      dirs[path].totalSize += size;
      path = path.parent_path();
    }
    dirs[path].totalSize += size;
  }

  int space        = 70000000;
  int least        = 30000000;
  int free         = space - dirs["/"].totalSize;
  int toDelete     = least - free;
  int bestDeletion = space;
  int sum          = 0;
  for (auto& [path, dir] : dirs) {
    if (dir.totalSize <= 100000) {
      sum += dir.totalSize;
    }
    if (dir.totalSize >= toDelete) {
      bestDeletion = std::min(bestDeletion, dir.totalSize);
    }
  }

  expectEq(sum, 1428881);
  expectEq(bestDeletion, 10475598);

  return 0;
}
