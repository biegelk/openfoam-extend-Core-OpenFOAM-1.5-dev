/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Class
    Foam::SphericalTensor2D

Description
    Templated 2D sphericalTensor derived from VectorSpace adding construction
    from 1 component, element access using ii() member function and the
    inner-product (dot-product) and outer-product operators.

SourceFiles
    SphericalTensor2DI.H

\*---------------------------------------------------------------------------*/

#ifndef SphericalTensor2D_H
#define SphericalTensor2D_H

#include "VectorSpace.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class SphericalTensor2D Declaration
\*---------------------------------------------------------------------------*/

template<class Cmpt>
class SphericalTensor2D
:
    public VectorSpace<SphericalTensor2D<Cmpt>, Cmpt, 1>
{

public:

    // Member constants

        enum
        {
            rank = 2 // Rank of SphericalTensor2D is 2
        };


    // Static data members

        static const char* const typeName;
        static const char* componentNames[];
        static const SphericalTensor2D zero;
        static const SphericalTensor2D one;
        static const SphericalTensor2D I;
        static const SphericalTensor2D oneThirdI;
        static const SphericalTensor2D twoThirdsI;


    //- Component labeling enumeration
    enum components { II };


    // Constructors

        //- Construct null
        inline SphericalTensor2D();

        //- Construct given VectorSpace
        inline SphericalTensor2D
        (
            const VectorSpace<SphericalTensor2D<Cmpt>, Cmpt, 1>&
        );

        //- Construct given the component
        inline SphericalTensor2D(const Cmpt& tii);

        //- Construct from Istream
        inline SphericalTensor2D(Istream&);


    // Member Functions

        // Access

            inline const Cmpt& ii() const;
            inline Cmpt& ii();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Include inline implementations
#include "SphericalTensor2DI.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
