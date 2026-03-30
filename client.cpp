#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080
#define BUF_SIZE 4096

void send_all(int sock, const char *buf, size_t len)
{
    size_t sent = 0;
    while (sent < len)
    {
        ssize_t n = send(sock, buf + sent, len - sent, 0);
        if (n <= 0)
            return;
        sent += n;
    }
}

int main()
{
    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        return 1;
    }

    // Connect to server
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sock, (sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        return 1;
    }

    // Register user
    std::string username;
    std::cout << "Enter username: ";
    std::cin >> username;

    std::string reg = "REGISTER " + username + "\n";
    send_all(sock, reg.c_str(), reg.size());

    int choice;
    std::cout << "1 → Send file\n2 → Receive file\nChoice: ";
    std::cin >> choice;

    char buffer[BUF_SIZE];

    /* =======================
       SENDER
       ======================= */
    if (choice == 1)
    {
        std::string target, filename;

        std::cout << "Send file to: ";
        std::cin >> target;
        std::cout << "File name: ";
        std::cin >> filename;

        std::ifstream file(filename, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file\n";
            close(sock);
            return 1;
        }

        file.seekg(0, std::ios::end);
        long filesize = file.tellg();
        file.seekg(0);

        std::string header =
            "SEND_CLIENT " + target + " " + filename + " " +
            std::to_string(filesize) + "\n";

        send_all(sock, header.c_str(), header.size());

        while (file.good())
        {
            file.read(buffer, BUF_SIZE);
            send_all(sock, buffer, file.gcount());
        }

        file.close();
        std::cout << "File sent successfully.\n";
    }

    /* =======================
       RECEIVER
       ======================= */
    // Wait for server message
    else
    {
        while (true)
        {
            int n = recv(sock, buffer, BUF_SIZE - 1, 0);
            if (n <= 0)
            {
                std::cerr << "Server disconnected\n";
                close(sock);
                break;
            }

            buffer[n] = '\0';
            std::string recv_header(buffer);

            // Expect: FILE_FROM Alice Test.txt 42
            if (recv_header.rfind("FILE_FROM", 0) == 0)
            {
                std::string tag, sender, filename;
                long filesize;

                std::stringstream ss(recv_header);
                ss >> tag >> sender >> filename >> filesize;

                std::cout << "\n--- File received ---\n";
                std::cout << "From    : " << sender << "\n";
                std::cout << "File    : " << filename << "\n";
                std::cout << "Size    : " << filesize << " bytes\n";
                std::cout << "Content :\n\n";

                long received = 0;
                while (received < filesize)
                {
                    int r = recv(sock, buffer, BUF_SIZE, 0);
                    if (r <= 0)
                        break;

                    std::cout.write(buffer, r);
                    received += r;
                }

                std::cout << "\n\n--- End of file ---\n";
                break;
            }
        }
        close(sock);
        return 0;
    }
}
