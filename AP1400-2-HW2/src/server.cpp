#include "server.h"

std::vector<std::string> pending_trxs;

Server::Server () {
    this->clients.clear();
}

void show_wallets(const Server& server) {
    std::cout << std::string(20, '*') << std::endl;
    for(const auto& client: server.clients)
        std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
    std::cout << std::string(20, '*') << std::endl;
}

std::shared_ptr<Client> Server::add_client (std::string id) {
    while (this->get_client(id) != nullptr) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1000, 9999);
        int rand = distrib(gen);
        if (this->get_client(id + std::to_string(rand)) != nullptr) continue;
        id += std::to_string(rand);
    }

    std::shared_ptr<Client> client_ptr = std::make_shared<Client>(id, *this);
    this->clients[client_ptr] = 5;
    return client_ptr;
}

std::shared_ptr<Client> Server::get_client (const std::string id) const {
    for (const auto& client : this->clients) {
        if (client.first->get_id() == id)
            return client.first;
    }
    return nullptr;
}

double Server::get_wallet (const std::string id) {
    for (const auto& client : this->clients) {
        if (client.first->get_id() == id)
            return client.second;
    }
    return 0;
}

bool Server::parse_trx (std::string trx, std::string& sender, std::string& receiver, double& value) {
    try {
        size_t nextPos1 = trx.find("-", 0);
        size_t nextPos2 = trx.find("-", nextPos1 + 1);
        sender = trx.substr(0, nextPos1);
        receiver = trx.substr(nextPos1 + 1, nextPos2 - nextPos1 - 1);
        value = std::stod(trx.substr(nextPos2 + 1));
        return true;
    } catch (const std::exception& e) {
        throw std::runtime_error("This transaction is invalid!");
        return false;
    }
}

bool Server::add_pending_trx (std::string trx, std::string signature) {
    std::string sender, receiver;
    double value;
    if (parse_trx(trx, sender, receiver, value) == false)
        return false;

    std::shared_ptr<Client> senderClient = get_client(sender), receiverClient = get_client(receiver);
    if (senderClient == nullptr || receiverClient == nullptr)
        return false;

    bool authentic = crypto::verifySignature(senderClient->get_publickey(), senderClient->get_id(), signature);
    if (authentic == false)
        return false;
    
    if (senderClient->get_wallet() < value)
        return false;
    
    pending_trxs.push_back(trx);
    return true;
}

size_t Server::mine() {
    std::string mempool = "";
    for (auto trx : pending_trxs) {
        mempool += trx;
        std::string sender, receiver;
        double value;
        parse_trx(trx, sender, receiver, value);
        for (auto& client : this->clients) {
            if (client.first->get_id() == sender) client.second -= value;
            if (client.first->get_id() == receiver) client.second += value;
        }
    }

    size_t nonce = 0;
    bool findNonce = false;
    while (findNonce == false) {
        for (auto& client : this->clients) {
            size_t genNonce = client.first->generate_nonce();
            std::string hash = crypto::sha256(mempool + std::to_string(genNonce));
            if (hash.find("000") <= 7) {
                client.second += 6.25;
                nonce = genNonce;
                findNonce = true;
            }
        }
    }
    pending_trxs.clear();
    return nonce;
}