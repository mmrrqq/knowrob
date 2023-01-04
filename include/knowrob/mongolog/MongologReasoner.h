/*
 * Copyright (c) 2022, Daniel Beßler
 * All rights reserved.
 *
 * This file is part of KnowRob, please consult
 * https://github.com/knowrob/knowrob for license details.
 */

#ifndef __KNOWROB_MONGOLOG_REASONER_H__
#define __KNOWROB_MONGOLOG_REASONER_H__

// STD
#include <memory>
// KnowRob
#include <knowrob/terms.h>
#include <knowrob/IReasoner.h>
#include <knowrob/prolog/PrologReasoner.h>

namespace knowrob {
	class MongologReasoner : public PrologReasoner {
	public:
		MongologReasoner(const std::string &reasonerID);
		~MongologReasoner();
		
		// Override IReasoner
		bool isCurrentPredicate(const PredicateIndicator &predicate) override;
		
	protected:
		
		// Override PrologReasoner
		std::shared_ptr<Query> transformQuery(const std::shared_ptr<Query> &q) override;

		// Override PrologReasoner
		bool initializeDefaultPackages() override;
    };
}

#endif //__KNOWROB_MONGOLOG_REASONER_H__
