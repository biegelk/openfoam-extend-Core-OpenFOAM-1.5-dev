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

\*----------------------------------------------------------------------------*/

#include "receivingReferralList.H"

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

receivingReferralList::receivingReferralList()
:
    labelListList(),
    sourceProc_(-1)
{}


receivingReferralList::receivingReferralList
(
    const label sourceProc,
    const labelListList& refCellsToSendTo
)
:
    labelListList(refCellsToSendTo),
    sourceProc_(sourceProc)
{}


receivingReferralList::receivingReferralList
(
    const receivingReferralList& rL
)
:
    labelListList(rL),
    sourceProc_(rL.sourceProc())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

receivingReferralList::~receivingReferralList()
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void receivingReferralList::operator=(const receivingReferralList& rhs)
{
    // Check for assignment to self
    if (this == &rhs)
    {
        FatalErrorIn
        (
            "Foam::receivingReferralList::operator="
            "(const Foam::receivingReferralList&)"
        )
            << "Attempted assignment to self"
            << abort(FatalError);
    }

    labelListList::operator=(rhs);

    sourceProc_ = rhs.sourceProc();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

bool operator==
(
    const receivingReferralList& a,
    const receivingReferralList& b
)
{
    // Trivial reject: lists are different size
    if (a.size() != b.size())
    {
        return false;
    }

    // Or if source processors are not the same.
    if (a.sourceProc() != b.sourceProc())
    {
        return false;
    }

    List<bool> fnd(a.size(), false);

    forAll (b, bI)
    {
        labelList curLList = b[bI];

        bool found = false;

        forAll (a, aI)
        {
            if (a[aI] == curLList)
            {
                found = true;
                fnd[aI] = true;
                break;
            }
        }

        if (!found)
        {
            return false;
        }
    }

    // check if all LLists on a were marked
    bool result = true;

    forAll (fnd, aI)
    {
        result = (result && fnd[aI]);
    }

    return result;
}


Istream& operator>>(Istream& is, receivingReferralList& rRL)
{
    is >> rRL.sourceProc_ >> static_cast<labelListList&>(rRL);

    is.check
    (
        "Istream& operator<<(Istream& f, const receivingReferralList& rRL"
    );

    return is;
}


Ostream& operator<<
(
    Ostream& os,
    const receivingReferralList& rRL
)
{
    os << rRL.sourceProc() << token::SPACE
        << static_cast< const labelListList& >(rRL);

    os.check
    (
        "Ostream& operator<<(Ostream& f, const receivingReferralList& rRL"
    );

    return os;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// ************************************************************************* //
