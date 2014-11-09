#ifndef Magnum_SceneGraph_TranslationTransformation_h
#define Magnum_SceneGraph_TranslationTransformation_h
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
 * @brief Class @ref Magnum::SceneGraph::TranslationTransformation, alias @ref Magnum::SceneGraph::BasicTranslationTransformation2D, @ref Magnum::SceneGraph::BasicTranslationTransformation3D, typedef @ref Magnum::SceneGraph::TranslationTransformation2D, @ref Magnum::SceneGraph::BasicTranslationTransformation3D
 */

#include "Magnum/Math/Matrix3.h"
#include "Magnum/Math/Matrix4.h"
#include "Magnum/SceneGraph/AbstractTranslation.h"
#include "Magnum/SceneGraph/Object.h"

namespace Magnum { namespace SceneGraph {

/**
@brief Translation-only transformation

Uses @ref Math::Vector2 or @ref Math::Vector3 as underlying type. By default
the translation is stored with the same underlying type as resulting
transformation matrix, but it's possible to store translation in e.g. integral
coordinates while having floating-point transformation matrix.

Note that translation is commutative, so all @ref TransformationType parameters
have no effect and are included only for compatibility with other
transformation implementations.

@see @ref BasicTranslationTransformation2D, @ref BasicTranslationTransformation3D,
    @ref TranslationTransformation2D, @ref TranslationTransformation3D,
    @ref scenegraph
*/
#ifdef DOXYGEN_GENERATING_OUTPUT
template<UnsignedInt dimensions, class T, class TranslationType = T>
#else
template<UnsignedInt dimensions, class T, class TranslationType>
#endif
class TranslationTransformation: public AbstractTranslation<dimensions, T, TranslationType> {
    public:
        /** @brief Underlying transformation type */
        typedef VectorTypeFor<dimensions, TranslationType> DataType;

        /** @brief Object transformation */
        VectorTypeFor<dimensions, TranslationType> transformation() const { return _transformation; }

        /**
         * @brief Set transformation
         * @return Reference to self (for method chaining)
         */
        Object<TranslationTransformation<dimensions, T, TranslationType>>& setTransformation(const VectorTypeFor<dimensions, TranslationType>& transformation) {
            /* Setting transformation is forbidden for the scene */
            /** @todo Assert for this? */
            /** @todo Do this in some common code so we don't need to include Object? */
            if(!static_cast<Object<TranslationTransformation<dimensions, T, TranslationType>>*>(this)->isScene()) {
                _transformation = transformation;
                static_cast<Object<TranslationTransformation<dimensions, T, TranslationType>>*>(this)->setDirty();
            }

            return static_cast<Object<TranslationTransformation<dimensions, T, TranslationType>>&>(*this);
        }

        /** @copydoc AbstractTranslation::resetTransformation() */
        Object<TranslationTransformation<dimensions, T, TranslationType>>& resetTransformation() {
            return setTransformation({});
        }

        /**
         * @brief Transform object
         * @return Reference to self (for method chaining)
         *
         * Equivalent to @ref translate(), provided only for compatibility with
         * other implementations. There is no difference between global and
         * local transformation.
         */
        Object<TranslationTransformation<dimensions, T, TranslationType>>& transform(const VectorTypeFor<dimensions, TranslationType>& transformation) {
            return translate(transformation);
        }

        #ifdef MAGNUM_BUILD_DEPRECATED
        /**
         * @copybrief transform()
         * @deprecated Use @ref Magnum::SceneGraph::TranslationTransformation::transform() "transform()"
         *      instead.
         */
        CORRADE_DEPRECATED("use transform() instead") Object<TranslationTransformation<dimensions, T, TranslationType>>& transform(const VectorTypeFor<dimensions, TranslationType>& transformation, TransformationType) {
            return transform(transformation);
        }
        #endif

        /**
         * @brief Translate object
         * @return Reference to self (for method chaining)
         *
         * There is no difference between global and local translation.
         * @see @ref Math::Vector2::xAxis(), @ref Math::Vector2::yAxis(),
         *      @ref Math::Vector3::xAxis(), @ref Math::Vector3::yAxis(),
         *      @ref Math::Vector3::zAxis()
         */
        Object<TranslationTransformation<dimensions, T, TranslationType>>& translate(const VectorTypeFor<dimensions, TranslationType>& vector) {
            _transformation += vector;
            return static_cast<Object<TranslationTransformation<dimensions, T, TranslationType>>&>(*this);
        }

        #ifdef MAGNUM_BUILD_DEPRECATED
        /**
         * @copybrief translate()
         * @deprecated Use @ref Magnum::SceneGraph::TranslationTransformation::translate() "translate()"
         *      instead.
         */
        CORRADE_DEPRECATED("use translate() instead") Object<TranslationTransformation<dimensions, T, TranslationType>>& translate(const VectorTypeFor<dimensions, TranslationType>& vector, TransformationType) {
            return translate(vector);
        }
        #endif

    protected:
        /* Allow construction only from Object */
        explicit TranslationTransformation() = default;

    private:
        void doResetTransformation() override final { resetTransformation(); }

        void doTranslate(const VectorTypeFor<dimensions, TranslationType>& vector) override final {
            translate(vector);
        }
        void doTranslateLocal(const VectorTypeFor<dimensions, TranslationType>& vector) override final {
            translate(vector);
        }

        VectorTypeFor<dimensions, TranslationType> _transformation;
};

/**
@brief Base transformation for two-dimensional scenes supporting translation

Convenience alternative to `TranslationTransformation<2, T, TranslationType>`.
See @ref TranslationTransformation for more information.
@see @ref TranslationTransformation2D, @ref BasicTranslationTransformation3D
*/
#ifdef DOXYGEN_GENERATING_OUTPUT
template<class T, class TranslationType = T>
#else
template<class T, class TranslationType>
#endif
using BasicTranslationTransformation2D = TranslationTransformation<2, T, TranslationType>;

/**
@brief Base transformation for two-dimensional float scenes supporting translation

@see @ref TranslationTransformation3D
*/
typedef BasicTranslationTransformation2D<Float> TranslationTransformation2D;

/**
@brief Base transformation for three-dimensional scenes supporting translation

Convenience alternative to `TranslationTransformation<3, T, TranslationType>`.
See @ref TranslationTransformation for more information.
@see @ref TranslationTransformation3D, @ref BasicTranslationTransformation2D
*/
#ifdef DOXYGEN_GENERATING_OUTPUT
template<class T, class TranslationType = T>
#else
template<class T, class TranslationType>
#endif
using BasicTranslationTransformation3D = TranslationTransformation<3, T, TranslationType>;

/**
@brief Base transformation for three-dimensional float scenes supporting translation

@see @ref TranslationTransformation2D
*/
typedef BasicTranslationTransformation3D<Float> TranslationTransformation3D;

namespace Implementation {

template<UnsignedInt dimensions, class T, class TranslationType> struct Transformation<TranslationTransformation<dimensions, T, TranslationType>> {
    static VectorTypeFor<dimensions, TranslationType> fromMatrix(const MatrixTypeFor<dimensions, T>& matrix) {
        CORRADE_ASSERT((matrix.rotationScaling() == Math::Matrix<dimensions, T>()),
           "SceneGraph::TranslationTransformation: the matrix doesn't represent pure translation", {});
        return VectorTypeFor<dimensions, TranslationType>{matrix.translation()};
    }

    constexpr static MatrixTypeFor<dimensions, T> toMatrix(const VectorTypeFor<dimensions, TranslationType>& transformation) {
        return MatrixTypeFor<dimensions, T>::translation(VectorTypeFor<dimensions, T>{transformation});
    }

    static VectorTypeFor<dimensions, TranslationType> compose(const VectorTypeFor<dimensions, TranslationType>& parent, const VectorTypeFor<dimensions, TranslationType>& child) {
        return parent+child;
    }

    static VectorTypeFor<dimensions, TranslationType> inverted(const VectorTypeFor<dimensions, TranslationType>& transformation) {
        return -transformation;
    }
};

}

#if defined(CORRADE_TARGET_WINDOWS) && !defined(__MINGW32__)
extern template class MAGNUM_SCENEGRAPH_EXPORT Object<TranslationTransformation<2, Float>>;
extern template class MAGNUM_SCENEGRAPH_EXPORT Object<TranslationTransformation<3, Float>>;
#endif

}}

#endif
