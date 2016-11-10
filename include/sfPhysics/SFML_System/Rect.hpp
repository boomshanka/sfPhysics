////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_RECT_HPP
#define SFML_RECT_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <sfPhysics/SFML_System/Vector2.hpp>
#include <algorithm>


namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Utility class for manipulating 2D axis aligned rectangles
///
////////////////////////////////////////////////////////////
template <typename T>
class Rect
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates an empty rectangle (it is equivalent to calling
    /// Rect(0, 0, 0, 0)).
    ///
    ////////////////////////////////////////////////////////////
    Rect();

    ////////////////////////////////////////////////////////////
    /// \brief Construct the rectangle from its coordinates
    ///
    /// Be careful, the last two parameters are the width
    /// and height, not the right and bottom coordinates!
    ///
    /// \param left   Left coordinate of the rectangle
    /// \param top    Top coordinate of the rectangle
    /// \param width  Width of the rectangle
    /// \param height Height of the rectangle
    ///
    ////////////////////////////////////////////////////////////
    Rect(T left, T top, T width, T height);

    ////////////////////////////////////////////////////////////
    /// \brief Construct the rectangle from position and size
    ///
    /// Be careful, the last parameter is the size,
    /// not the bottom-right corner!
    ///
    /// \param position Position of the top-left corner of the rectangle
    /// \param size     Size of the rectangle
    ///
    ////////////////////////////////////////////////////////////
    Rect(const Vector2<T>& position, const Vector2<T>& size);

    ////////////////////////////////////////////////////////////
    /// \brief Check if a point is inside the rectangle's area
    ///
    /// \param x X coordinate of the point to test
    /// \param y Y coordinate of the point to test
    ///
    /// \return True if the point is inside, false otherwise
    ///
    /// \see Intersects
    ///
    ////////////////////////////////////////////////////////////
    bool Contains(T x, T y) const;

    ////////////////////////////////////////////////////////////
    /// \brief Check if a point is inside the rectangle's area
    ///
    /// \param point Point to test
    ///
    /// \return True if the point is inside, false otherwise
    ///
    /// \see Intersects
    ///
    ////////////////////////////////////////////////////////////
    bool Contains(const Vector2<T>& point) const;

    ////////////////////////////////////////////////////////////
    /// \brief Check the intersection between two rectangles
    ///
    /// \param rectangle Rectangle to test
    ///
    /// \return True if rectangles overlap, false otherwise
    ///
    /// \see Contains
    ///
    ////////////////////////////////////////////////////////////
    bool Intersects(const Rect<T>& rectangle) const;

    ////////////////////////////////////////////////////////////
    /// \brief Check the intersection between two rectangles
    ///
    /// This overload returns the overlapped rectangle in the
    /// \a intersection parameter.
    ///
    /// \param rectangle    Rectangle to test
    /// \param intersection Rectangle to be filled with the intersection
    ///
    /// \return True if rectangles overlap, false otherwise
    ///
    /// \see Contains
    ///
    ////////////////////////////////////////////////////////////
    bool Intersects(const Rect<T>& rectangle, Rect<T>& intersection) const;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    T Left;   ///< Left coordinate of the rectangle
    T Top;    ///< Top coordinate of the rectangle
    T Width;  ///< Width of the rectangle
    T Height; ///< Height of the rectangle
};

#include <sfPhysics/SFML_System/Rect.inl>

// Create typedefs for the most common types
typedef Rect<int>   IntRect;
typedef Rect<float> FloatRect;

} // namespace sf


#endif // SFML_RECT_HPP


////////////////////////////////////////////////////////////
/// \class sf::Rect
/// \ingroup graphics
///
/// A rectangle is defined by its top-left corner and its size.
/// It is a very simple class defined for convenience, so
/// its member variables (Left, Top, Width and Height) are public
/// and can be accessed directly, just like the vector classes
/// (Vector2 and Vector3).
///
/// To keep things simple, sf::Rect doesn't define
/// functions to emulate the properties that are not directly
/// members (such as Right, Bottom, Center, etc.), it rather
/// only provides intersection functions.
///
/// sf::Rect uses the usual rules for its boundaries:
/// \li The Left and Top edges are included in the rectangle's area
/// \li The right (Left + Width) and bottom (Top + Height) edges are excluded from the rectangle's area
///
/// This means that sf::IntRect(0, 0, 1, 1) and sf::IntRect(1, 1, 1, 1)
/// don't intersect.
///
/// sf::Rect is a template and may be used with any numeric type, but
/// for simplicity the instanciations used by SFML are typedefed:
/// \li sf::Rect<int> is sf::IntRect
/// \li sf::Rect<float> is sf::FloatRect
///
/// So that you don't have to care about the template syntax.
///
/// Usage example:
/// \code
/// // Define a rectangle, located at (0, 0) with a size of 20x5
/// sf::IntRect r1(0, 0, 20, 5);
///
/// // Define another rectangle, located at (4, 2) with a size of 18x10
/// sf::Vector2i position(4, 2);
/// sf::Vector2i size(18, 10);
/// sf::IntRect r2(position, size);
///
/// // Test intersections with the point (3, 1)
/// bool b1 = r1.Contains(3, 1); // true
/// bool b2 = r2.Contains(3, 1); // false
///
/// // Test the intersection between r1 and r2
/// sf::IntRect result;
/// bool b3 = r1.Intersects(r2, result); // true
/// // result == (4, 2, 16, 3)
/// \endcode
///
////////////////////////////////////////////////////////////