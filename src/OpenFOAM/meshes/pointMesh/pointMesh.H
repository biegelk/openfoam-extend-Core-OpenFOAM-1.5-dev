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
    Foam::pointMesh

Description
    Mesh representing a set of points created from polyMesh.

\*---------------------------------------------------------------------------*/

#ifndef pointMesh_H
#define pointMesh_H

#include "GeoMesh.H"
#include "polyMesh.H"
#include "pointBoundaryMesh.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class pointMesh Declaration
\*---------------------------------------------------------------------------*/

class pointMesh
:
    public GeoMesh<polyMesh>
{
    // Permanent data

        //- Boundary mesh
        pointBoundaryMesh boundary_;


    // Private Member Functions

        //- Map all fields
        void mapFields(const mapPolyMesh&);

        //- Disallow default bitwise copy construct
        pointMesh(const pointMesh&);

        //- Disallow default bitwise assignment
        void operator=(const pointMesh&);


public:

    typedef pointMesh Mesh;
    typedef pointBoundaryMesh BoundaryMesh;


    // Constructors

        //- Construct from polyMesh
        explicit pointMesh
        (
            const polyMesh& pMesh,
            bool alwaysConstructGlobalPatch = false
        );


    // Member Functions

        //- Return number of points
        label size() const
        {
            return size(*this);
        }

        //- Return number of points
        static label size(const Mesh& mesh)
        {
            return mesh.mesh_.nPoints();
        }

        //- Return number of points
        //  Needed because point and elemant fields in FEM share
        //  templated patch field type(checking of patch size).
        //  HJ, 16/Oct/2008
        label nPoints() const
        {
            return mesh_.nPoints();
        }

        //- Return number of points
        //  Needed because point and elemant fields in FEM share
        //  templated patch field type(checking of patch size).
        //  HJ, 16/Oct/2008
        label nCells() const
        {
            return mesh_.nCells();
        }

        //- Return reference to boundary mesh
        const pointBoundaryMesh& boundary() const
        {
            return boundary_;
        }

        //- Return parallel info
        const globalMeshData& globalData() const
        {
            return mesh_.globalData();
        }


        // Mesh motion

            //- Move points, returns volumes swept by faces in motion
            void movePoints(const pointField&);

            //- Update the mesh corresponding to given map
            void updateMesh(const mapPolyMesh& mpm);


    // Member Operators

        bool operator!=(const pointMesh& pm) const
        {
            return &pm != this;
        }

        bool operator==(const pointMesh& pm) const
        {
            return &pm == this;
        }
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
