#ifndef Magnum_SceneGraph_AbstractTranslationRotationScaling2D_h
#define Magnum_SceneGraph_AbstractTranslationRotationScaling2D_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Class @ref Magnum::SceneGraph::AbstractBasicTranslationRotationScaling2D, typedef @ref Magnum::SceneGraph::AbstractTranslationRotationScaling2D
 */

#include "Magnum/SceneGraph/AbstractTranslationRotation2D.h"

namespace Magnum { namespace SceneGraph {

/**
@brief Base transformation for two-dimensional scenes supporting translation, rotation and scaling

@see @ref AbstractTranslationRotationScaling2D, @ref scenegraph,
    @ref AbstractBasicTranslationRotationScaling2D,
    @ref BasicMatrixTransformation2D
*/
template<class T> class AbstractBasicTranslationRotationScaling2D: public AbstractBasicTranslationRotation2D<T> {
    public:
        explicit AbstractBasicTranslationRotationScaling2D() = default;

        /**
         * @brief Scale object
         * @return Reference to self (for method chaining)
         *
         * @see @ref scaleLocal(), @ref Math::Vector2::xScale(),
         *      @ref Math::Vector2::yScale()
         */
        AbstractBasicTranslationRotationScaling2D<T>& scale(const Math::Vector2<T>& vector) {
            doScale(vector);
            return *this;
        }

        /**
         * @brief Scale object as a local transformation
         *
         * Similar to the above, except that the transformation is applied
         * before all others.
         */
        AbstractBasicTranslationRotationScaling2D<T>& scaleLocal(const Math::Vector2<T>& vector) {
            doScaleLocal(vector);
            return *this;
        }

        #ifdef MAGNUM_BUILD_DEPRECATED
        /**
         * @copybrief scale()
         * @deprecated Use @ref Magnum::SceneGraph::AbstractTranslationRotationScaling2D::scale() "scale()"
         *      or @ref Magnum::SceneGraph::AbstractTranslationRotationScaling2D::scaleLocal() "scaleLocal()"
         *      instead.
         */
        CORRADE_DEPRECATED("use scale() or scaleLocal() instead") AbstractBasicTranslationRotationScaling2D<T>& scale(const Math::Vector2<T>& vector, TransformationType type) {
            return type == TransformationType::Global ? scale(vector) : scaleLocal(vector);
        }
        #endif

        /* Overloads to remove WTF-factor from method chaining order */
        #ifndef DOXYGEN_GENERATING_OUTPUT
        AbstractBasicTranslationRotationScaling2D<T>& resetTransformation() {
            AbstractBasicTranslationRotation2D<T>::resetTransformation();
            return *this;
        }
        AbstractBasicTranslationRotationScaling2D<T>& translate(const Math::Vector2<T>& vector) {
            AbstractBasicTranslationRotation2D<T>::translate(vector);
            return *this;
        }
        AbstractBasicTranslationRotationScaling2D<T>& translateLocal(const Math::Vector2<T>& vector) {
            AbstractBasicTranslationRotation2D<T>::translateLocal(vector);
            return *this;
        }
        #ifdef MAGNUM_BUILD_DEPRECATED
        CORRADE_DEPRECATED("use translate() or translateLocal() instead") AbstractBasicTranslationRotationScaling2D<T>& translate(const Math::Vector2<T>& vector, TransformationType type) {
            AbstractBasicTranslationRotation2D<T>::translate(vector, type);
            return *this;
        }
        #endif
        AbstractBasicTranslationRotationScaling2D<T>& rotate(Math::Rad<T> angle) {
            AbstractBasicTranslationRotation2D<T>::rotate(angle);
            return *this;
        }
        AbstractBasicTranslationRotationScaling2D<T>& rotateLocal(Math::Rad<T> angle) {
            AbstractBasicTranslationRotation2D<T>::rotateLocal(angle);
            return *this;
        }
        #ifdef MAGNUM_BUILD_DEPRECATED
        CORRADE_DEPRECATED("use rotate() or rotateLocal() instead") AbstractBasicTranslationRotationScaling2D<T>& rotate(Math::Rad<T> angle, TransformationType type) {
            AbstractBasicTranslationRotation2D<T>::rotate(angle, type);
            return *this;
        }
        #endif
        #endif

    protected:
        ~AbstractBasicTranslationRotationScaling2D() = default;

    #ifdef DOXYGEN_GENERATING_OUTPUT
    protected:
    #else
    private:
    #endif
        /** @brief Polymorphic implementation for @ref scale() */
        virtual void doScale(const Math::Vector2<T>& vector) = 0;

        /** @brief Polymorphic implementation for @ref scaleLocal() */
        virtual void doScaleLocal(const Math::Vector2<T>& vector) = 0;
};

/**
@brief Base transformation for two-dimensional float scenes supporting translation, rotation and scaling

@see @ref AbstractTranslationRotationScaling3D
*/
typedef AbstractBasicTranslationRotationScaling2D<Float> AbstractTranslationRotationScaling2D;

}}

#endif
