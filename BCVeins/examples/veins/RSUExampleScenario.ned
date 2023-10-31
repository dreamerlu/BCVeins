//
// Copyright (C) 2017 Christoph Sommer <sommer@ccs-labs.org>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.Scenario;
import org.car2x.veins.base.modules.Switch;


network RSUExampleScenario extends Scenario
{
    types:
        channel myChannel extends ned.DelayChannel {
            delay = 100ms;
        };
    submodules:
        rsu[3]: RSU {
            @display("p=150,140;i=veins/sign/yellowdiamond;is=vs");
        }
        switch: Switch;
    connections allowunconnected:
        rsu[0].gateOut++ --> switch.gateIn++;
        switch.gateOut++ --> rsu[0].gateIn++;

        rsu[1].gateOut++ --> switch.gateIn++;
        switch.gateOut++ --> rsu[1].gateIn++;

        rsu[2].gateOut++ --> switch.gateIn++;
        switch.gateOut++ --> rsu[2].gateIn++;

}
