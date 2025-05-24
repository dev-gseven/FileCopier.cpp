#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

void copiarTitulo(){

    std::string caminho_pasta;
    std::cout << "Insert the folder directory:\n";
    std::getline(std::cin, caminho_pasta);

    #ifdef _WIN32
    std::string caminho_arquivo_final = caminho_pasta + "\\" + "name_of_files.txt";
    #else
    std::string caminho_arquivo_final = caminho_pasta + "/" + "name_of_files.txt";
    #endif

    std::ofstream arquivo_saida(caminho_arquivo_final);

    if (!arquivo_saida) {
        std::cerr << "Error while creating the text file!\n";
        return;
    }

    for (const auto& entrada : std::filesystem::directory_iterator(caminho_pasta)) {
        if (std::filesystem::is_regular_file(entrada)) {
            arquivo_saida << entrada.path().filename().string() << std::endl;
        }
    }
    std::cout << "Name of files saved in '" << caminho_arquivo_final << "'" << std::endl;
}


void copiarArquivo() {

    std::string caminho_inicio;
    std::string caminho_fim;

    std::cout << "Insert the starting directory:\n";
    std::getline(std::cin, caminho_inicio);

    std::cout << "Insert the final directory:\n";
    std::getline(std::cin, caminho_fim);

    std::string filename;
    std::vector<std::string> nome;

    std::cout << "Insert the file/extension name:\n";
    std::getline(std::cin, filename);

    for (const auto& iterator : std::filesystem::directory_iterator(caminho_inicio)){
        std::string arquivo = iterator.path().filename().string();
        
        if (arquivo.find(filename) != std::string::npos) {
            nome.push_back(arquivo);
        }
    }

    std::string origem;
    std::string destino;

    for (const std::string& iterator : nome){

        #ifdef _WIN32
        std::string origem = caminho_inicio + "\\" + iterator;
        std::string destino = caminho_fim + "\\" + iterator;
        #else 
        std::string origem = caminho_inicio + "/" + iterator;
        std::string destino = caminho_fim + "/" + iterator;
        #endif

        std::ifstream arquivoOrigem(origem, std::ios::binary);
        std::ofstream arquivoDestino(destino, std::ios::binary);

        if (!arquivoOrigem) {
        std::cerr << "Error while opening the starting directory!\n";
        return;
    }
        if (!arquivoDestino) {
        std::cerr << "Error while opening the final directory!\n";
        return;
    }
        std::vector<char> buffer(4096);
        while (arquivoOrigem.read(buffer.data(), buffer.size())){
            arquivoDestino.write(buffer.data(), arquivoOrigem.gcount());
        }
        arquivoDestino.write(buffer.data(), arquivoOrigem.gcount());

        std::cout << "File: '" << iterator << "' successfully copied!\n";
    }
}

void menu(){
    bool running{true};
    while (running){
        std::cout   << "=== Main Menu ===\n"
                    << "1 - Copy the title of all files of a folder to .txt\n"
                    << "2 - Copy files with specific name/extension to another folder\n"
                    << "3 - Exit\n"
                    << "Choose one option: ";
        int opcao{};
        std::cin >> opcao;
        std::cin.ignore();
        switch(opcao){
            case 1:
            copiarTitulo();
            break;
            case 2:
            copiarArquivo();
            break;
            case 3:
            running = false;
            break;
            default:
            std::cout << "Invalid option!\n";
            break;
        }
    }
}


int main() {
    std::cout << "Welcome to the FileCopier.cpp!\n";
    menu();
    return 0;
}