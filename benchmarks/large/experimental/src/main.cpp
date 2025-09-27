//Copyright Florian Goujeon 2021.
//Distributed under the Boost Software License, Version 1.0.
//(See accompanying file LICENSE or copy at
//https://www.boost.org/LICENSE_1_0.txt)
//Official repository: https://github.com/fgoujeon/fsm-benchmark

#include "common.hpp"
#include <maki.hpp>
#include <functional>
#include <queue>

namespace libfsm
{
    using state_index = int;

    template<class Context, const auto& StateMoldPtrs, class TransitionTypeList>
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

        using state_mold_ptr_constant_list =
            maki::detail::tuple_to_element_ptr_constant_list_t<StateMoldPtrs>;

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
                state_mold_ptr_constant_list,
                process_event_in_active_state>::call(*this, event) ||
            maki::detail::tlu::apply_t<
                TransitionTypeList,
                process_event_in_transition_table>::call(*this, event);
        }

        template<class... StateMoldPtrConstants>
        struct process_event_in_active_state
        {
            template<class Event>
            static bool call(machine& self, const Event& event)
            {
                return (
                    self.template try_process_event_in_state<StateMoldPtrConstants>(event) ||
                    ...);
            }
        };

        template<class StateMoldPtrConstant, class Event>
        bool try_process_event_in_state(const Event& event)
        {
            constexpr const auto& state_mold = **StateMoldPtrConstant::value;
            constexpr const auto& internal_actions =
                maki::detail::impl_of(state_mold).internal_actions;
            constexpr const auto& internal_action =
                maki::detail::tuple_get<0>(internal_actions);

            if constexpr (internal_action.evt_set.template contains<Event>())
            {
                constexpr auto state_index =
                    maki::detail::tlu::find_v<
                        state_mold_ptr_constant_list,
                    StateMoldPtrConstant>;

                if (state_index == active_state_index_)
                {
                    internal_action.action(ctx_, event);
                    return true;
                }
            }
            return false;
        }

        template<class... Transitions>
        struct process_event_in_transition_table
        {
            template<class Event>
            static bool call(machine& self, const Event& event)
            {
                return (self.try_execute_transition<Transitions>(event) || ...);
            }
        };

        template<class Transition, class Event>
        bool try_execute_transition(const Event& event)
        {
            if constexpr (std::is_same_v<Event, typename Transition::event_type>)
            {
                using source_state_mold_ptr_constant =
                    maki::detail::tlu::get_t<
                        state_mold_ptr_constant_list,
                        Transition::source_state_index>;
                constexpr const auto& source_state_mold =
                    **source_state_mold_ptr_constant::value;
                constexpr const auto& source_state_exit_actions =
                    maki::detail::impl_of(source_state_mold).exit_actions;
                constexpr const auto& source_state_exit_action =
                    maki::detail::tuple_get<0>(source_state_exit_actions);

                if (active_state_index_ == Transition::source_state_index && Transition::grd(event))
                {
                    Transition::act(ctx_, event);
                    source_state_exit_action.action(*this);
                    active_state_index_ = Transition::target_state_index;
                    return true;
                }
                return false;
            }
            else
            {
                return false;
            }
        }

        Context ctx_;
        state_index active_state_index_ = 0;
        processing_queue_type processing_queue_;
        bool processing_event_ = false;
    };
}

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
constexpr auto state = maki::state_mold{}
    .internal_action_ce<internal_transition_event>(
        [](context& ctx, const internal_transition_event& evt)
        {
            ctx.counter /= evt.two;
        })
    .exit_action_m(
        [](auto& mach)
        {
            mach.process_event(internal_transition_event{});
        });

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

template<int Index>
struct transition
{
    static constexpr auto source_state_index = Index;
    static constexpr auto target_state_index = (Index + 1) % PROBLEM_SIZE;
    using event_type = state_transition_event<Index>;
    static constexpr auto grd = &guard<Index>;
    static constexpr auto act = &state_transition_action<Index>;
};

constexpr auto state_mold_ptrs = maki::detail::make_tuple(
    maki::detail::distributed_construct
#define X(N) \
    , &state<N>
    COUNTER
#undef X
);

using transition_type_list = maki::detail::type_list_t<
#define X(N) \
    COMMA_IF_NOT_0(N) transition<N>
    COUNTER
#undef X
>;

int test()
{
    auto sm = libfsm::machine<context, state_mold_ptrs, transition_type_list>{};

    for(auto i = 0; i < test_loop_size; ++i)
    {
#define X(N) \
    sm.process_event_now(state_transition_event<N>{});
        COUNTER
#undef X
    }

    return sm.context().counter;
}
