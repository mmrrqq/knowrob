/*
 * Copyright (c) 2022, Daniel Beßler
 * All rights reserved.
 *
 * This file is part of KnowRob, please consult
 * https://github.com/knowrob/knowrob for license details.
 */

#ifndef __KNOWROB_IREASONER_H__
#define __KNOWROB_IREASONER_H__

#include "knowrob/lang/PredicateIndicator.h"
#include "knowrob/lang/Query.h"
#include "knowrob/qa/AnswerStream.h"

namespace knowrob {
    /**
     * The interface for reasoning subsystems.
     */
    class IReasoner {
    public:
        virtual ~IReasoner(){}

        /** Initialize this reasoner.
         * This will only be called once when the reasoner is loaded.
         * @todo is it certain run is not called while initialization is still ongoing?
         */
        virtual void initialize() = 0;

        /** Find out whether this reasoner can handle a given predicate.
         *
         * Note that, following the Syntax of the querying language,
         * for a reasoner to be able to answer the `,\2` predicate entails that the
         * reasoner can handle conjunctive queries, `;\2` disjunctive queries etc.
         *
         * @param predicate the predicate in question
         * @return true if the reasoner can determine the truth of given predicate.
         */
        virtual bool canReasonAbout(const PredicateIndicator &predicate) const = 0;

        /** Run the reasoner to answer a given query.
         *
         * This function is usually called in a separate thread.
         * Hence, make sure IReasoner implementations are thread-safe.
         * The status is set to active before this function is called,
         * and can be updated within the call to indicate different states of the reasoner.
         * Note that the status is also used to indicate that it has been requested to
         * terminate this reasoning process.
         *
         * @param goal the query made of predicates that can be answered by the reasoner
         * @param status indicates the current reasoning status
         * @param answerQueue the publisher for answers generated by the reasoner if any
         * @return the status of processing the given goal
         */
        virtual void run(const IQuery &goal, ReasoningStatus &status, MessageQueue<Answer> &answerQueue) = 0;
    };
}

#endif //__KNOWROB_IREASONER_H__
