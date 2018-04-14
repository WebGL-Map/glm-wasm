/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Tyler Bucher
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef GLM_WASM_BLOCKTRAIT_H
#define GLM_WASM_BLOCKTRAIT_H

#include <string>

namespace glmwasm {

    /**
     * Represents an individual block state.
     *
     * @author Tyler Bucher
     */
    class BlockTrait {
    private:

        /**
         * The name of the trait.
         */
        const std::string *name;

        /**
         * The value of the trait.
         */
        const std::string *value;

    public:

        /**
         * Creates a BlockTrait by passing pointers to the location of the values.
         *
         * @param name the pointer to the name of the trait..
         * @param value the pointer to the value of the trait.
         */
        BlockTrait(const std::string *name, const std::string *value);

        /**
         * @return the name of the trait.
         */
        const std::string *getName() const;

        /**
         * @return the value of the trait.
         */
        const std::string *getValue() const;

        /**
         * This operator should only return true if the types and members are equal.
         *
         * @param b the compared block type.
         *
         * @return true if the types and members are equal.
         */
        bool operator==(const BlockTrait &b) const;

        /**
         * Removes the block trait.
         */
        virtual ~BlockTrait();
    };
}

#endif //GLM_WASM_BLOCKTRAIT_H
