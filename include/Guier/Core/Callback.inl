/*
* MIT License
*
* Copyright(c) 2018 Jimmie Bergmann
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/
/*
// Signal implementations
template <typename Return, typename... Arguments>
Signal<Return(Arguments...)>::~Signal()
{
    DisconnectAll();
}

template <typename Return, typename... Arguments>
template <typename Class, typename Function>
std::shared_ptr<Connection> Signal<Return(Arguments...)>::Connect(Class * p_pClass, const Function & p_Function)
{
    std::lock_guard<std::mutex> sm(m_Mutex); // Lock mutex.

    auto binding = Bind(p_Function, p_pClass, MakeIntSequence<sizeof...(Arguments)>{});
    auto connection = std::make_shared<Connection>();
    connection->m_pSignal = this;
    connection->m_pSlot = nullptr;

    auto pair = std::make_pair(connection, binding);

    if (std::is_base_of<Slot, Class>::value)
    {
        Slot * pSlot = reinterpret_cast<Slot *>(p_pClass);
        connection->m_pSlot = pSlot;
        pSlot->m_pConnections.insert(reinterpret_cast<ConnectionBase *>(connection.get()));
    }

    m_Bindings.push_back(pair);

    return connection;
}

template <typename Return, typename... Arguments>
std::shared_ptr<Connection> Signal<Return(Arguments...)>::Connect(const CallbackFunction & p_Function)
{
    std::lock_guard<std::mutex> sm(m_Mutex); // Lock mutex.

    auto connection = std::make_shared<Connection>();
    connection->m_pSignal = this;
    connection->m_pSlot = nullptr;
    auto pair = std::make_pair(connection, p_Function);

    m_Bindings.push_back(pair);

    return connection;
}

template <typename Return, typename... Arguments>
void Signal<Return(Arguments...)>::DisconnectAll()
{
    std::lock_guard<std::mutex> sm(m_Mutex); // Lock mutex.

    for (auto it = m_Bindings.begin(); it != m_Bindings.end(); it++)
    {
        it->first.get()->m_pSignal = nullptr;
        if (it->first.get()->m_pSlot)
        {
            it->first.get()->m_pSlot->RemoveConnection(it->first.get());
        }
        it->first.get()->m_pSlot = nullptr;
    }
    m_Bindings.clear();
}

template <typename Return, typename... Arguments>
Return Signal<Return(Arguments...)>::operator()(Arguments... p_Arguments)
{
    std::lock_guard<std::mutex> sm(m_Mutex); // Lock mutex.

    for (auto it = m_Bindings.begin(); it != m_Bindings.end(); it++)
    {
        it->second(std::forward<Arguments>(p_Arguments)...);
    }

    return Return();
}

template <typename Return, typename... Arguments>
void Signal<Return(Arguments...)>::Disconnect(Connection * p_pConnection)
{
    std::lock_guard<std::mutex> sm(m_Mutex); // Lock mutex.

    for (auto it = m_Bindings.begin(); it != m_Bindings.end(); it++)
    {
        if (it->first.get() == p_pConnection)
        {
            it->first.get()->m_pSignal = nullptr;
            if (it->first.get()->m_pSlot)
            {
                it->first.get()->m_pSlot->RemoveConnection(it->first.get());
            }
            it->first.get()->m_pSlot = nullptr;
            m_Bindings.erase(it);
            return;
        }
    }

    // ERROR!!!
    std::runtime_error("Could not find binding to disconnect.");
}

template <typename Return, typename... Arguments>
void Signal<Return(Arguments...)>::DisconnectFromSlot(Connection * p_pConnection)
{
    std::lock_guard<std::mutex> sm(m_Mutex); // Lock mutex.

    for (auto it = m_Bindings.begin(); it != m_Bindings.end(); it++)
    {
        if (it->first.get() == p_pConnection)
        {
            it->first.get()->m_pSignal = nullptr;
            it->first.get()->m_pSlot = nullptr;
            m_Bindings.erase(it);
            return;
        }
    }

    // ERROR!!!
    std::runtime_error("Could not find binding to disconnect.");
}
*/