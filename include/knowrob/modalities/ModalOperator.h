//
// Created by daniel on 22.03.23.
//

#ifndef KNOWROB_MODAL_OPERATOR_H
#define KNOWROB_MODAL_OPERATOR_H

#include <list>
#include "knowrob/terms/Term.h"
#include "knowrob/modalities/Modality.h"

namespace knowrob {
    /**
     * The type of a modal operator.
     */
    enum class ModalOperatorType {
        NECESSITY,
        POSSIBILITY
    };

    /**
     * An operator of a modal language, e.g. "B" is often used for "belief" and
     * "K" for "knowledge".
     */
    class ModalOperator : public Term {
    public:
        ModalOperator(const Modality *modality, ModalOperatorType operatorType);

        /**
         * @return the modality associated to this operator.
         */
        const auto* modality() const { return modality_; }

        /**
         * @return the type of this operator.
         */
        auto modalOperatorType() const { return operatorType_; }

        /**
         * @return true if the accessibility relation of this modality is transitive.
         */
        bool isTransitive() const;

        /**
         * @return true if the accessibility relation of this modality is euclidean.
         */
        bool isEuclidean() const;

        /**
         * @return the symbol of this modal operator.
         */
        const char* symbol() const;

        // Override Term
        bool isGround() const override { return true; }

        // Override Term
        bool isAtomic() const override { return true; }

        // Override Term
        const VariableSet& getVariables() override { return Term::noVariables_; }

        // Override Term
        void write(std::ostream& os) const override;

    protected:
        const Modality *modality_;
        const ModalOperatorType operatorType_;

        // Override Term
        bool isEqual(const Term &other) const override;
    };

    /**
     * An iteration over modalities.
     * Each iteration corresponds to applying the accessibility relation once.
     */
    class ModalIteration {
    public:
        ModalIteration() = default;

        /**
         * @param other another iteration.
         * @return true if this and other are the same iterations.
         */
        bool operator==(const ModalIteration &other) const;

        /**
         * @return number of operators in this sequence.
         */
        auto numOperators() const { return modalitySequence_.size(); }

        /**
         * @param modalOperator add an operator to this iteration.
         */
        void push_back(const ModalOperator &modalOperator);

        /**
         * @return begin iterator of modal operators.
         */
        auto begin() const { return modalitySequence_.begin(); }

        /**
         * @return end iterator of modal operators.
         */
        auto end() const { return modalitySequence_.end(); }

        /**
         * @return an empty iteration.
         */
        static const std::shared_ptr<ModalIteration>& emptyIteration();

    protected:
        std::list<ModalOperator> modalitySequence_;
    };

} // knowrob

#endif //KNOWROB_MODAL_OPERATOR_H
