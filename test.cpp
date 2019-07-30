#include <string>
#include <iostream>

using namespace std;

string GetStdoutFromCommand(string cmd) {

	string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");

	stream = popen(cmd.c_str(), "r");
	if (stream) {
		while (!feof(stream))
			if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
		pclose(stream);
	}
	data = data.substr(0, data.length() - 1);
	return data;
}

int main (){

string ls = GetStdoutFromCommand("ls | wc -l");

cout << ls << ' ' << ls.length() << endl;

return 0;

}
