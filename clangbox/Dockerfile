FROM alpine:3.10
LABEL maintainer="Georg Rollinger <georg.rollinger@posteo.net>"
ENV clang_version=8.0.0-r0
LABEL description="Clang Format ${clang_version}"
RUN apk add --no-cache clang=${clang_version} git jq
COPY .clang-format /.clang-format
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]