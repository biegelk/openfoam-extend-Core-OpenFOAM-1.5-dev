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
    Foam::HeatTransferModel


Description
    Templated heat transfer model class

SourceFiles
    HeatTransferModel.C
    NewHeatTransferModel.C

\*---------------------------------------------------------------------------*/

#ifndef HeatTransferModel_H
#define HeatTransferModel_H

#include "IOdictionary.H"
#include "autoPtr.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                       Class HeatTransferModel Declaration
\*---------------------------------------------------------------------------*/

template<class CloudType>
class HeatTransferModel
{

    // Private data

        //- The cloud dictionary
        const dictionary& dict_;

        //- Reference to the owner cloud class
        CloudType& owner_;

        //- The coefficents dictionary
        const dictionary coeffDict_;


public:

    //- Runtime type information
    TypeName("HeatTransferModel");

    //- Declare runtime constructor selection table
    declareRunTimeSelectionTable
    (
        autoPtr,
        HeatTransferModel,
        dictionary,
        (
            const dictionary& dict,
            CloudType& owner
        ),
        (dict, owner)
    );


    // Constructors

        //- Construct from dictionary
        HeatTransferModel
        (
            const dictionary& dict,
            CloudType& owner,
            const word& type
        );


    // Destructor

        virtual ~HeatTransferModel();


    // Selector

        static autoPtr<HeatTransferModel<CloudType> > New
        (
            const dictionary& dict,
            CloudType& owner
        );


    // Access

        //- Return the cloud dictionary
        const dictionary& dict() const;

        //- Return the coefficients dictionary
        const dictionary& coeffDict() const;

        //- Return the owner cloud object
        const CloudType& owner() const;


    // Member Functions

        //- Flag to indicate whether model activates heat transfer model
        virtual bool active() const = 0;

        //- Nusselt number
        virtual scalar Nu
        (
            const scalar Re,
            const scalar Pr
        ) const = 0;

        //- Prandtl number
        virtual scalar Pr() const = 0;

        //- Return heat transfer coefficient
        scalar h
        (
            const scalar dp,
            const vector& Ur,
            const scalar rhoc,
            const scalar rhop,
            const scalar cpc,
            const scalar cpp,
            const scalar muc
        ) const;

        //- Return linearised coefficient for temperature equation
        scalar Cu
        (
            const scalar dp,
            const vector& Ur,
            const scalar rhoc,
            const scalar rhop,
            const scalar cpc,
            const scalar cpp,
            const scalar muc
        ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define makeHeatTransferModel(CloudType)                                      \
                                                                              \
    defineNamedTemplateTypeNameAndDebug(HeatTransferModel<CloudType>, 0);     \
                                                                              \
    defineTemplateRunTimeSelectionTable                                       \
    (                                                                         \
        HeatTransferModel<CloudType>,                                         \
        dictionary                                                            \
    );


#define makeHeatTransferModelType(SS, CloudType, ParcelType)                  \
                                                                              \
    defineNamedTemplateTypeNameAndDebug(SS<CloudType<ParcelType> >, 0);       \
                                                                              \
    HeatTransferModel<CloudType<ParcelType> >::                               \
        adddictionaryConstructorToTable<SS<CloudType<ParcelType> > >          \
            add##SS##CloudType##ParcelType##ConstructorToTable_;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "HeatTransferModel.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
