:- module(temporal_workflow,
	[ workflow_sequence(r,t)
	]).
/** <module> Reasoning about plans.

@author Daniel Beßler
*/

:- use_module(library('semweb/rdf_db'),
    [ rdf_has/3 ]).
:- use_module(library('rdf_test')).
:- use_module('interval',
	[ interval_constraint/3 ]).
:- use_module('esg',
	[ esg_truncated/4, esg_event_sequence/2 ]).

%% workflow_sequence(+WF, ?StepSequence) is semidet.
%
% StepSequence is an ordered sequence of steps that are steps
% of the workflow WF.
% WF may also be a list of individual tasks with temporal relations
% between them.
%
% @param WF A workflow or a list of steps.
% @param StepSequence An ordered list of steps.
%
workflow_sequence(WF, StepSequence) :-
	\+ is_list(WF),!,
	findall(S, rdf_has(WF,soma:hasStep,S), Steps),
	workflow_sequence(Steps, StepSequence).
  
workflow_sequence(Steps, StepSequence) :-
	findall(Constraint, (
		member(X,Steps),
		interval_constraint(X,Constraint,Other),
		member(Other,Steps)
	), Constraints),
	%
	esg_truncated(tsk, Steps, Constraints, [Sequence,_,_]),
	esg_event_sequence(Sequence, [_|StepSequence]).

		 /*******************************
		 *	    UNIT TESTS	     		*
		 *******************************/

:- begin_rdf_tests(temporal_workflow, 'owl/test/pancake.owl').

:- sw_register_prefix(test, 'http://knowrob.org/kb/pancake.owl#').

test('WF_MakingPancakes_0 steps') :-
	findall(S, rdf_has(test:'WF_MakingPancakes_0',soma:hasStep,S), Steps),
	assert_true(member(test:'Mixing_0',Steps)),
	assert_true(member(test:'Baking_0',Steps)),
	assert_unifies(Steps,[_,_]).

test('WF_MakingPancakes_0 sequence', [nondet]) :-
	workflow_sequence(test:'WF_MakingPancakes_0',
		[ test:'Mixing_0',
		  test:'Baking_0'
		]).

test('WF_Baking_0 sequence', [nondet]) :-
	workflow_sequence(test:'WF_Baking_0',
		[ test:'TurningOn_0',
		  test:'Pouring_0',
		  test:'FlippingAPancake_0'
		]).

:- end_rdf_tests(temporal_workflow).
