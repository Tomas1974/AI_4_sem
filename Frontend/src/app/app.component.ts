import {ChangeDetectorRef, Component, OnInit} from '@angular/core';
import {DataService} from "./Data.service";
import {LegendPosition} from "@swimlane/ngx-charts";

import {chatbox} from "ionicons/icons";
import {DataMockService} from "./DataMock.service";
import {UtilitiesService} from "./utilities.service";

@Component({
  selector: 'app-root',
  template: `

    <ion-content scrollY="true">

      <ion-col>
        <ion-row>
          <img style=" width: 2%; height: auto;" src="../assets/Temp_image.jpg">

          <H1 style="margin-left: 20px;">AI temperature</H1>
        </ion-row>
      </ion-col>

      <br>
      <br>
      <br>

      <ion-grid>
        <ion-row>
          <ion-col size="7">

            <ion-card >
            <ion-row>
              <ion-col>
              <ion-button (click)="nameGraph()">Name</ion-button>
                <ion-button (click)="start_stop()">Start/Stop</ion-button>
              <ion-button (click)="saveGraph()">Save</ion-button>
              </ion-col>
                <ion-col>
                  <h1>{{graphName}}</h1>

              </ion-col>
            </ion-row>






              <ngx-charts-line-chart
                [view]=[1000,400]
                [scheme]="colorScheme"
                [legend]="showLegend"
                [showXAxisLabel]="showXAxisLabel"
                [showYAxisLabel]="showYAxisLabel"
                [animations]="true"
                [xAxis]="xAxis"
                [yAxis]="yAxis"
                [xAxisLabel]="xAxisLabel"
                [yAxisLabel]="yAxisLabel"
                [timeline]="timeline"
                [results]="this.dataService.temperatureData"
                (select)="onSelect($event)"
                (activate)="onActivate($event)"
                (deactivate)="onDeactivate($event)"

              >
              </ngx-charts-line-chart>


            </ion-card>

          </ion-col>

          <ion-col size="6">
            <ion-card >

            <ion-row>
              <p>Antal målinger {{ dataService.temperatureData.length }}</p>
            </ion-row>
            <ion-button (click)="nulstil()">Nulstil</ion-button>
            </ion-card>
          </ion-col>
        </ion-row>
      </ion-grid>
    </ion-content>
  `,

})
export class AppComponent {


  // options

  showLegend = true;
  showXAxisLabel = true;
  xAxisLabel = 'Sec';
  yAxisLabel = 'Temperatures';
  showYAxisLabel = true;
  xAxis: boolean = true;
  yAxis: boolean = true;
  timeline: boolean = true;



  colorScheme: any  = {
    domain: ['#A10A28', '#C7B42C', '#5AA454','#AAAAAA']
  };

  legendPosition=LegendPosition.Below; //placerer landene under grafen

  graphName: string="";


  constructor(public dataService: DataService, public utilitiesService: UtilitiesService ) {

    }


  onSelect(event:any) {
    console.log(event);
  }


  onActivate(event:any): void {
    console.log(event)
  }

  onDeactivate(event:any): void {
    console.log(event)
  }



  async nulstil() {

    let confirm=await this.utilitiesService.confirmDelete()

    if (confirm) {
      this.dataService.nulstil();
      this.graphName="";
    }
  }


  async nameGraph() {
    this.graphName=await this.utilitiesService.insertLine("Save Name","","");
  }

   saveGraph() {

  }

  start_stop() {

  }
}
