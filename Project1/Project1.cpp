#include <iostream>
#include <unistd.h>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    int pipeID, filePipe[2], bufferSizePipe[2];
    char* bufferSizeDynamic;

    pipe(filePipe);
    pipe(bufferSizePipe);
    pipeID = fork();
    if (pipeID == 0) {
        //open the file
        ifstream inputFile(argv[1], fstream::binary);
        //find the length of the file for the buffer
        inputFile.seekg(0, inputFile.end);
        int bufferLength = inputFile.tellg();
        inputFile.seekg(0, inputFile.beg);
        //do some janky stuff to get the length into a char*
        bufferSizeDynamic = to_string(bufferLength).data();

        //setup buffer
        char* buffer = new char[bufferLength];

        //read in the data
        inputFile.read(buffer, bufferLength);
        //close file
        inputFile.close();

        write(filePipe[1], buffer, bufferLength);
        //writing a second pipe to allow for dynamic sizing of the file's information
        //uses sizeof(int) since there's no good reason for it to be bigger than 2.147bil
        //it can always ba changed to long long.
        //This needs to be piped as well since it will get lost in the processes if not piped
        //Also reads the file size to a second pipe used for the buffer
        write(bufferSizePipe[1], bufferSizeDynamic, sizeof(int));
    }
    else {
        //create the holder for the buffer size
        bufferSizeDynamic = new char;
        //read in the buffer size
        read(bufferSizePipe[0], bufferSizeDynamic, sizeof(int));
        //change the size to an int and store it since it's used more than once
        int dynamicBufferSize = stoi(bufferSizeDynamic);
        //Initialise the buffer used for storing the file's info
        char* buffer = new char[dynamicBufferSize];
        //read from the pipe into the buffer
        read(filePipe[0], buffer, dynamicBufferSize);
        //open the file
        ofstream outFile(argv[2], fstream::binary);
        //write to the file
        outFile.write(buffer, dynamicBufferSize);
        outFile.close();
    }

    return 0;
}