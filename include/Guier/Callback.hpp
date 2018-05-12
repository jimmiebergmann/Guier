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

#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <chrono>
#include <iostream>


#include <functional>
#include <algorithm>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <memory>
#include <Guier/Core/Build.hpp>
#include <exception>

namespace Guier
{

    namespace Callback
    {

        template<int>
        struct PlaceholderSignal
        {
        };


        // Forward declarations
        class Slot;

        class ConnectionBase;

        class Connection;

        template <typename>
        class Signal;

        class SignalBase
        {

        public:

            friend class Connection;

        protected:

            virtual void Disconnect(Connection * p_pConnection) = 0;
            virtual void DisconnectFromSlot(Connection * p_pConnection) = 0;

        };


        // Signal class
        template <typename Return, typename... Arguments>
        class Signal<Return(Arguments...)> : public SignalBase
        {

        public:

            typedef std::function<Return(Arguments...)> CallbackFunction;

            ~Signal();

            template <typename Class, typename Function>
            std::shared_ptr<Connection> Connect(Class * p_pClass, const Function & p_Function);

            std::shared_ptr<Connection> Connect(const CallbackFunction & p_Function);

            void DisconnectAll();

            Return operator()(Arguments... p_Arguments);

        private:

            virtual void Disconnect(Connection * p_pConnection);
            virtual void DisconnectFromSlot(Connection * p_pConnection);

            template<int... Ns>
            struct IntSequence
            {
            };

            template<int N, int... Ns>
            struct MakeIntSequence
                : MakeIntSequence<N - 1, N - 1, Ns...>
            {
            };

            template<int... Ns>
            struct MakeIntSequence<0, Ns...>
                : IntSequence<Ns...>
            {
            };

            template<typename T, typename U, int... Ns>
            CallbackFunction Bind(const T& fn, U *p, IntSequence<Ns...>) const
            {
                return std::bind(fn, p, PlaceholderSignal<Ns>{}...);
            }

            // Private variables
            typedef std::list<std::pair<std::shared_ptr<Connection>, CallbackFunction>> BindingsList;
            BindingsList m_Bindings;

        };


        // Base class for connection.
        class ConnectionBase
        {

        public:

            friend class Slot;

            virtual void Disconnect() = 0;

        protected:

            virtual void DisconnectFromSlot() = 0;

        };


        // Slot class
        class Slot
        {

        public:

            template <typename>
            friend class Signal;

            virtual ~Slot();

        private:

            void RemoveConnection(ConnectionBase * p_pConnection);

            typedef std::set<ConnectionBase *> ConnectionSet;

            ConnectionSet m_pConnections;

        };


        // Connection class.
        class Connection : public ConnectionBase
        {

        public:

            template <typename>
            friend class Signal;

            friend class Slot;

            Connection();

            virtual void Disconnect();

        private:

            virtual void DisconnectFromSlot();



            //CallbackFunction m_Callback;
            SignalBase * m_pSignal;
            Slot *		 m_pSlot;

        };


        // Include inline implementations. 
        #include <Guier/Core/Callback.inl>

    }

}


namespace std
{
    template<int N>
    struct is_placeholder<Guier::Callback::PlaceholderSignal<N>>
        : integral_constant<int, N + 1>
    {
    };
}