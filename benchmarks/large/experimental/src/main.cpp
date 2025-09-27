//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "common.hpp"
#include <maki.hpp>
#include <functional>
#include <queue>

struct context
{
    int counter = 0;
};

template<int Index>
struct state_transition_event
{
    int two = 2;
};

struct internal_transition_event
{
    int two = 2;
};

template<int Index>
struct state
{
    template<class Event>
    static bool try_execute_internal_action(context& /*ctx*/, const Event& /*evt*/)
    {
        return false;
    }

    static bool try_execute_internal_action(context& ctx, const internal_transition_event& evt)
    {
        ctx.counter /= evt.two;
        return true;
    }

    template<class Machine>
    static void execute_exit_action(Machine& mach)
    {
        mach.process_event(internal_transition_event{});
    }

    static constexpr auto index = Index;
};

template<int Index>
void state_transition_action(context& ctx, const state_transition_event<Index>& evt)
{
    ctx.counter = (ctx.counter + 1) * evt.two;
}

template<int Index>
bool guard(const state_transition_event<Index>& evt)
{
    return evt.two >= 0;
}

namespace libfsm
{
    using state_index = int;

    template<int Index>
    struct transition
    {
        template<class Context, class Machine, class Event>
        static bool try_execute(Context& /*ctx*/, Machine& /*mach*/, state_index& /*active_state_index*/, const Event& /*event*/)
        {
            return false;
        }

        template<class Context, class Machine>
        static bool try_execute(Context& ctx, Machine& mach, state_index& active_state_index, const state_transition_event<Index>& event)
        {
            if (active_state_index == Index && guard<Index>(event))
            {
                state_transition_action<Index>(ctx, event);
                state<Index>::execute_exit_action(mach);
                active_state_index = (Index + 1) % PROBLEM_SIZE;
                return true;
            }
            return false;
        }
    };

    using state_type_list = maki::detail::type_list_t<
#define X(N) \
    COMMA_IF_NOT_0(N) state<N>
        COUNTER
#undef X
    >;

    using transition_type_list = maki::detail::type_list_t<
#define X(N) \
    COMMA_IF_NOT_0(N) transition<N>
        COUNTER
#undef X
    >;

    template<class Context>
    class machine
    {
    public:
        template<class Event>
        void process_event(const Event& event)
        {
            if (!processing_event_)
            {
                process_event_now(event);
            }
            else
            {
                processing_queue_.template push<any_event_visitor>(event);
            }
        }

        template<class Event>
        void process_event_now(const Event& event)
        {
            processing_event_ = true;

            process_one_event(event);

            processing_queue_.invoke_and_pop_all(*this);

            processing_event_ = false;
        }

        Context& context()
        {
            return ctx_;
        }

    private:
        using processing_queue_type = maki::detail::function_queue<
            machine&,
            sizeof(int)>;

        struct any_event_visitor
        {
            template<class Event>
            static void call(const Event& event, machine& self)
            {
                self.process_one_event(event);
            }
        };

        template<class Event>
        void process_one_event(const Event& event)
        {
            maki::detail::tlu::apply_t<
                state_type_list,
                process_event_in_active_state>::call(*this, event) ||
            maki::detail::tlu::apply_t<
                transition_type_list,
                process_event_in_transition_table>::call(*this, event);
        }

        template<class... States>
        struct process_event_in_active_state
        {
            template<class Event>
            static bool call(machine& self, const Event& event)
            {
                return (self.template try_process_event_in_state<States>(event) || ...);
            }
        };

        template<class State, class Event>
        bool try_process_event_in_state(const Event& event)
        {
            if (State::index == active_state_index_)
            {
                return State::try_execute_internal_action(ctx_, event);
            }
            return false;
        }

        template<class... Transitions>
        struct process_event_in_transition_table
        {
            template<class Event>
            static bool call(machine& self, const Event& event)
            {
                return (Transitions::try_execute(self.ctx_, self, self.active_state_index_, event) || ...);
            }
        };

        Context ctx_;
        state_index active_state_index_ = 0;
        processing_queue_type processing_queue_;
        bool processing_event_ = false;
    };
}

int test()
{
    auto sm = libfsm::machine<context>{};

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(N) \
    sm.process_event_now(state_transition_event<N>{});
        COUNTER
#undef X
    }

    return sm.context().counter;
}
