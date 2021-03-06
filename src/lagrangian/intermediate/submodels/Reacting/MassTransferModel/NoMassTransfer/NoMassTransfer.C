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

\*---------------------------------------------------------------------------*/

#include "NoMassTransfer.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template <class CloudType>
Foam::NoMassTransfer<CloudType>::NoMassTransfer
(
    const dictionary& dict,
    CloudType& cloud
)
:
    MassTransferModel<CloudType>(dict, cloud, typeName)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template <class CloudType>
Foam::NoMassTransfer<CloudType>::~NoMassTransfer()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool Foam::NoMassTransfer<CloudType>::active() const
{
    return false;
}


template<class CloudType>
bool Foam::NoMassTransfer<CloudType>::changesVolume() const
{
    return false;
}


template<class CloudType>
Foam::scalar Foam::NoMassTransfer<CloudType>::calculate
(
    const scalar,
    const scalar,
    const scalar,
    const scalarField&,
    const scalarField&,
    const scalar,
    bool& canCombust
) const
{
    // Model does not stop combustion taking place
    canCombust = true;

    // Nothing more to do...
    return 0.0;
}


// ************************************************************************* //
