#include "ApiRequest.hpp"

ApiRequest::ApiRequest(const QUrl& url) :
    m_url(url)
{
}

QUrl ApiRequest::url() const
{
    return m_url;
}

