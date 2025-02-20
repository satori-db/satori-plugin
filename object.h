#include<string>
#include<vector>
#include<nlohmann/json.hpp>
#include<plusaes/plusaes.hpp>
#include<iostream>
#pragma once

using namespace nlohmann;

namespace Satori {
	class Object {
	public:

	

		std::string key;
		std::vector<json> vertices = {};
		std::string type = "normal";
		bool expires = 0;
		bool is_encrypted = false;
		long long expiration_time = -1;
		json data;
		std::string encrypted_data;
		std::vector<std::string> references;

		Object();
		Object(std::string _key);
		void from_json(json js);
		
		json to_json();

		void encrypt(std::string encryption_key);

		void decrypt(std::string encryption_key);

		std::string to_string();
	};

	inline std::vector<unsigned char> enc_decc(std::string str){
			std::vector<unsigned char> uns;

			for (int i = 0; i < str.size(); i++) {
				uns.push_back((unsigned char)str[i]);
			}

			return uns;
	}

	inline void Satori::Object::encrypt(std::string encryption_key) {
		char raw_key[17];
		std::string ec = encryption_key;
		for (int i = 0; i < ec.size(); i++) {
			raw_key[i] = ec[i];
		}
		const std::vector<unsigned char> key = plusaes::key_from_string(&raw_key);
		const unsigned char iv[16] = {
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		};
		std::string dt = this->to_json().dump();
		const unsigned long encrypted_size = plusaes::get_padded_encrypted_size(dt.size());
		std::vector<unsigned char> encrypted(encrypted_size);

		plusaes::encrypt_cbc((unsigned char*)dt.data(), dt.size(), &key[0], key.size(), &iv, &encrypted[0], encrypted_size, 1);
		std::string serialized = "";
		for (int i = 0; i < encrypted.size(); i++) {
			serialized += encrypted[i];
		}

		encrypted_data = serialized;
		data = {};
		expiration_time = -1;
		expires = 0;
		is_encrypted = 1;
		vertices = {};
		references = {};
	}

	inline std::string Satori::Object::to_string() {
		return this->to_json().dump();
	}

	inline json Satori::Object::to_json() {
		json dc;
		dc["key"] = key;
		dc["vertices"] = vertices;
		dc["type"] = type;
		dc["expires"] = expires;
		dc["is_encrypted"] = is_encrypted;
		dc["expiration_time"] = expiration_time;
		dc["encrypted_data"] = encrypted_data;
		dc["data"] = data;
		dc["references"] = references;
		return dc;
	}

	inline void Satori::Object::from_json(json js) {
		key = js["key"];
		vertices = js["vertices"];
		type = js["type"];
		expires = js["expires"];
		is_encrypted = js["is_encrypted"];
		expiration_time = js["expiration_time"];
		data = js["data"];
		encrypted_data = js["encrypted_data"];
		references = js["references"];
	}

	inline void Satori::Object::decrypt(std::string encryption_key) {
		try {
			std::vector<unsigned char> encrypted_str = enc_decc(encrypted_data);
			unsigned long padded = 0;
			std::vector<unsigned char> dec(encrypted_str.size());
			std::string key = encryption_key;
			char raw_key[17];
			for (int i = 0; i < key.size(); i++) {
				raw_key[i] = key[i];
			}

			auto coded_key = plusaes::key_from_string(&raw_key);
			const unsigned char iv[16] = {
				0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
				0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
			};
			plusaes::decrypt_cbc(&encrypted_str[0], encrypted_str.size(), &coded_key[0], coded_key.size(), &iv, &dec[0], dec.size(), &padded);
			std::string decrypted;
			for (int i = 0; i < dec.size(); i++) {
				decrypted += dec[i];
			}
			try
			{
				json x = json::parse(decrypted);
				from_json(x);
			}
			catch (const std::exception&)
			{
				
			}
		}
		catch (const std::exception&) {
			
		}
	}

	inline Object::Object() {
	}

	inline Object::Object(std::string _key) {
		key = _key;
	}
}

