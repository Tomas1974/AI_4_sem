export class BaseDto<T> {
  eventType: string;

  constructor(init?: Partial<T>) {
    this.eventType = this.constructor.name;
    Object.assign(this, init)
  }
}


export class ClientWantsToGetAllFarverDto extends BaseDto<ClientWantsToGetAllFarverDto> {
  farver?: string[];
}



export class ServerSendsIOTDataToClientsDto extends BaseDto<ServerSendsIOTDataToClientsDto> {
  data?: string;
}
