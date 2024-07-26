#include "client.h"
#include "server.h"

Client::Client (const std::string id, Server& server) : id(id), server(&server) {
    crypto::generate_key(this->public_key, this->private_key);
}

std::string Client::get_id () const {
    return this->id;
}

std::string Client::get_publickey () const {
    return this->public_key;
}

double Client::get_wallet () {
    return this->server->get_wallet(this->id);
}

std::string Client::sign (std::string txt) const {
    return crypto::signMessage(this->private_key, txt);
}

bool Client::transfer_money (std::string receiver, double value) {
    std::string trx = this->id + "-" + receiver + "-" + std::to_string(value);
    return this->server->add_pending_trx(trx, sign(this->id));
}

size_t Client::generate_nonce () {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, INT_MAX);
    return distrib(gen);
}