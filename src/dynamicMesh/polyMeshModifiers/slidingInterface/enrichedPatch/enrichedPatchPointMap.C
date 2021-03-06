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

Description
    Enriched patch point map

Author
    Hrvoje Jasak, Wikki Ltd.  All rights reserved.  Copyright Hrvoje Jasak.

\*---------------------------------------------------------------------------*/

#include "enrichedPatch.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::enrichedPatch::completePointMap() const
{
    if (pointMapComplete_)
    {
        FatalErrorIn("void enrichedPatch::completePointMap() const")
            << "Point map already completed"
            << abort(FatalError);
    }

    pointMapComplete_ = true;

    const Map<label>& pmm = pointMergeMap();

    // Get the mesh points for both patches.  If the point has not been
    // merged away, add it to the map

    // Do master patch
    const labelList& masterMeshPoints = masterPatch_.meshPoints();
    const pointField& masterLocalPoints = masterPatch_.localPoints();

    forAll (masterMeshPoints, pointI)
    {
        if 
        (
            !pmm.found(masterMeshPoints[pointI])
         && !pointMap_.found(masterMeshPoints[pointI])
        )
        {
            pointMap_.insert
            (
                masterMeshPoints[pointI],
                masterLocalPoints[pointI]
            );
        }
    }

    // Do slave patch
    const labelList& slaveMeshPoints = slavePatch_.meshPoints();
    const pointField& slaveLocalPoints = slavePatch_.localPoints();

    forAll (slaveMeshPoints, pointI)
    {
        if
        (
            !pmm.found(slaveMeshPoints[pointI])
         && !pointMap_.found(slaveMeshPoints[pointI])
        )
        {
            pointMap_.insert
            (
                slaveMeshPoints[pointI],
                slaveLocalPoints[pointI]
            );
        }
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


Foam::Map<Foam::point>& Foam::enrichedPatch::pointMap()
{
    return pointMap_;
}


const Foam::Map<Foam::point>& Foam::enrichedPatch::pointMap() const
{
    return pointMap_;
}


// ************************************************************************* //
