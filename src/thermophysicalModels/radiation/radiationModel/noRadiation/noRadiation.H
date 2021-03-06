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
    Foam::radiation::noRadiation

Description
    No radiation - does nothing to energy equation source terms
    (returns zeros)

SourceFiles
    noRadiation.C

\*---------------------------------------------------------------------------*/

#ifndef noRadiation_H
#define noRadiation_H

#include "radiationModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace radiation
{

/*---------------------------------------------------------------------------*\
                             Class noRadiation Declaration
\*---------------------------------------------------------------------------*/

class noRadiation
:
    public radiationModel
{

    // Private member functions

        //- Disallow default bitwise copy construct
        noRadiation(const noRadiation&);

        //- Disallow default bitwise assignment
        void operator=(const noRadiation&);


public:

    //- Runtime type information
    TypeName("noRadiation");


    // Constructors

        //- Construct from components
        noRadiation(const volScalarField& T);


    // Destructor

        ~noRadiation();


    // Member functions

        // Edit

            //- Update radiation source
            void correct();

            //- Read radiationProperties dictionary
            bool read();

            //- Source term component (for power of T^4)
            tmp<volScalarField> Rp() const;

            //- Source term component (constant)
            tmp<DimensionedField<scalar, volMesh> > Ru() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace radiation
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
