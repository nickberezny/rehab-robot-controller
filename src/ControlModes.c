/****************************************************************************
 * Copyright (C) 2012 by Matteo Franchin                                    *
 *                                                                          *
 * This file is part of Box.                                                *
 *                                                                          *
 *   Box is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Box is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file ControlModes.c
 * @author Nick Berezny
 * @date 26 Apr 2023
 * @
 *
 * Test test
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <stdbool.h>
#include <limits.h>

#include "./include/Parameters.h"
#include "./include/Structures.h"
#include "./include/ControlModes.h"
#include "./include/CUIC.h"

void PositionMode(struct States * s, struct ControlParams * p)
{

    BasicPD(s,p);
    return;
}


void AdmittanceMode(struct States * s, struct ControlParams * p)
{

    VirtualTrajectory(s,p);
    BasicPDxv(s,p);
    return;
}

void ImpedanceMode(struct States * s, struct ControlParams * p)
{
    //TODO: Test
    ComputedTorqueImp(s,p);
    return;
}

void UICMode(struct States * s, struct ControlParams * p)
{
      
    VirtualTrajectory(s,p);
    ComputedTorque(s,p);
    return;
}


void StochasticForceMode(struct States * s, struct ControlParams * p)
{
    //s->cmd = 0.0; 
    s->cmd = (((double)rand()/(double)RAND_MAX)-0.5)*2.0*p->Fmax;
    printf("stoch cmd: %.2f\n", (((double)rand()/(double)RAND_MAX)-0.5)*2.0*p->Fmax);
    return;
}

void AddRandomAmountToCommand(struct States * s, struct ControlParams * p)
{
    s->cmd += (((double)rand()/(double)RAND_MAX)-0.5)*2.0*p->Fmax;
    return;
}