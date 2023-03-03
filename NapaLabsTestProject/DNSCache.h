#ifndef DNSCACHE_HPP
#define DNSCACHE_HPP

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <regex>

std::mutex singleton_mutex;

class DNSCache
{
public:
    DNSCache(DNSCache const&) = delete;
    DNSCache& operator=(DNSCache const&) = delete;
    ~DNSCache() {}

    static DNSCache* get_instance(const size_t cache_size = 1)
    {
        std::lock_guard<std::mutex> lock(singleton_mutex);
        if (!instance)
        {
            instance = std::unique_ptr<DNSCache>(new DNSCache(cache_size));
        }
        return instance.get();
    }

    void update(const std::string& name, const std::string& ip) 
    {
        // O(1)
        std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
        
        if (!std::regex_match(ip, ipv4)) {
            return;
        }

        m_cache[name] = ip;
        if (m_cache.size() > m_cache_size) {
            auto first_element = m_cache.begin();
            m_cache.erase(first_element);
        }
    }

    std::string resolve(const std::string& name) const
    {
        // O(1)
        return m_cache.at(name);
    }

private:
    const size_t m_cache_size;
    std::unordered_map<std::string, std::string> m_cache;
    
    inline static std::unique_ptr<DNSCache> instance{ nullptr };
    explicit DNSCache(const size_t cache_size = 1) : m_cache_size{ cache_size } {}
};

#endif