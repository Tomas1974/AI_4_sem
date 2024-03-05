import {ChangeDetectorRef, Component, OnInit} from '@angular/core';
import {DataService} from "./Data.service";
import {LegendPosition} from "@swimlane/ngx-charts";
import {farveModel} from "./farveModel";
import {chatbox} from "ionicons/icons";

@Component({
  selector: 'app-root',
  template: `

    <ion-content scrollY="true">

      <ion-col>
        <ion-row>
          <img style=" width: 20%; height: auto;" src="../assets/smiley.png">

          <H1 style="margin-left: 20px;">Smiley</H1>
        </ion-row>
      </ion-col>

      <br>
      <br>
      <br>

      <ion-grid>
        <ion-row>
          <ion-col size="7">

            <ion-card >
              <ion-card-title>Antal af forskellige farver</ion-card-title>

              <ngx-charts-bar-vertical
                [view]=[1000,400]
                [scheme]="colorScheme"
                [results]="this.dataService.farve_count"
                [gradient]="gradient"
                [xAxis]="showXAxis"
                [yAxis]="showYAxis"
                [legend]="showLegend"
                [legendPosition]="legendPosition"
                [showXAxisLabel]="showXAxisLabel"
                [showYAxisLabel]="showYAxisLabel"
                [xAxisLabel]="xAxisLabel"
                [yAxisLabel]="yAxisLabel"
                (select)="onSelect($event)">
              </ngx-charts-bar-vertical>


            </ion-card>



          </ion-col>
          <ion-card >

            <ion-card-title>Procent fordeling</ion-card-title>
          <ngx-charts-pie-chart
            [view]=[1000,400]
            [scheme]="colorScheme"
            [results]="this.dataService.farve_procent"
            [gradient]="gradient"
            [legend]="showLegend"
            [legendPosition]="legendPosition"
            [labels]="showLabels"
            [doughnut]="isDoughnut"
            (select)="onSelect($event)"
            (activate)="onActivate($event)"
            (deactivate)="onDeactivate($event)"
          >
          </ngx-charts-pie-chart>
          </ion-card>

          <ion-col size="6">
            <ion-card >
            <ion-row>
              <p>Antal Rød {{ dataService.farve_count[0].value }}</p>
            </ion-row>
            <ion-row>
              <p>Antal Gul {{ dataService.farve_count[1].value }}</p>
            </ion-row>
            <ion-row>
              <p>Antal Grøn {{ dataService.farve_count[2].value }}</p>
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
  showXAxis = true;
  showYAxis = true;
  gradient = false;
  showLegend = true;
  showXAxisLabel = true;
  xAxisLabel = 'Farve';
  showYAxisLabel = true;
  yAxisLabel = 'Antal';
  showLabels: boolean = true;
  isDoughnut: boolean = false;


  colorScheme: any  = {
    domain: ['#A10A28', '#C7B42C', '#5AA454','#AAAAAA']
  };

  legendPosition=LegendPosition.Below; //placerer landene under grafen

  constructor(public dataService: DataService, private cdr: ChangeDetectorRef) {

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



  nulstil() {
    this.dataService.nulstil();
  }

  protected readonly chatbox = chatbox;
}
